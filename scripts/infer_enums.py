"""Mine raylib's own .c files (examples + src) for enum-constant uses in
RLAPI call sites, via clang's AST. Outputs a (function, argpos) -> enum
table inferred from real usage.

This is way more accurate than regex-on-comments:
  - For *every* example program raylib ships, every IsKeyDown(KEY_*)
    call is recorded as evidence that param 0 of IsKeyDown is a
    KeyboardKey.
  - Cross-reference uses raylib's own JSON to map enum-member -> enum.
  - We aggregate: for each (function, arg-position), report the
    dominant enum and confidence (% agreement across call sites).
"""
from __future__ import annotations
import json
import os
import re
import subprocess
import sys
from collections import Counter, defaultdict
from concurrent.futures import ThreadPoolExecutor, as_completed
from pathlib import Path

# Override either via env var. Defaults work if you've cloned raylib as
# a sibling directory (../raylib) and have clang on PATH.
CLANG = os.environ.get("CLANG_PATH", "clang")
RAYLIB_PATH = Path(os.environ.get("RAYLIB_PATH",
                                  Path(__file__).parent.parent / "raylib"))
RAYLIB_SRC = RAYLIB_PATH / "src"
RAYLIB_EXAMPLES = RAYLIB_PATH / "examples"
API_JSON = RAYLIB_PATH / "tools" / "rlparser" / "output" / "raylib_api.json"


def load_api(path: Path) -> dict:
    text = path.read_text(encoding="utf-8")
    pat = re.compile(r'^(\s*"description":\s*)"(.*)"(,?\s*)$')
    fixed = []
    for line in text.splitlines():
        m = pat.match(line)
        if m:
            body = m.group(2).replace('\\"', '\x00').replace('"', '\\"').replace('\x00', '\\"')
            line = m.group(1) + '"' + body + '"' + m.group(3)
        fixed.append(line)
    return json.loads('\n'.join(fixed))


def first_decl_ref_name(node):
    cur = node
    while isinstance(cur, dict):
        if cur.get("kind") == "DeclRefExpr":
            return cur.get("referencedDecl", {}).get("name")
        kids = cur.get("inner") or []
        if not kids:
            return None
        cur = kids[0]
    return None


def deepest_enum_member(node):
    """Drill through ImplicitCastExpr / ParenExpr / etc. looking for a
    DeclRefExpr that references an EnumConstantDecl. Returns the member
    name or None."""
    cur = node
    seen = 0
    while isinstance(cur, dict) and seen < 12:
        if cur.get("kind") == "DeclRefExpr":
            ref = cur.get("referencedDecl", {})
            if ref.get("kind") == "EnumConstantDecl":
                return ref.get("name")
            return None
        # If it's a binary-or expression like (FLAG_A | FLAG_B), all leaves
        # may be enum constants; collect the first we hit.
        kids = cur.get("inner") or []
        if not kids:
            return None
        cur = kids[0]
        seen += 1
    return None


_ARITH_BINOPS = {"|", "+", "-", "&", "^", "<<", ">>", "*"}
_PASSTHROUGH_KINDS = {
    "ImplicitCastExpr", "CStyleCastExpr", "ParenExpr",
    "UnaryOperator",  # also passes through; opcode irrelevant for our purpose
    "ConstantExpr",
}

def collect_or_enum_members(node, out: list[str]):
    """Walk *only* through the subtree of an argument expression that
    plausibly *is* the argument's value: arithmetic/bitwise combinations of
    literals and enum constants. Stop at ternaries, comparisons, function
    calls, struct literals, etc. — those can mention enum constants for
    *other* reasons (`x == GESTURE_TAP ? RED : LIGHTGRAY`) and would
    otherwise pollute the inference.
    """
    if isinstance(node, dict):
        kind = node.get("kind", "")
        if kind == "DeclRefExpr":
            ref = node.get("referencedDecl", {})
            if ref.get("kind") == "EnumConstantDecl":
                out.append(ref.get("name"))
            return
        if kind == "BinaryOperator":
            if node.get("opcode") in _ARITH_BINOPS:
                for c in node.get("inner") or []:
                    collect_or_enum_members(c, out)
            return
        if kind in _PASSTHROUGH_KINDS:
            for c in node.get("inner") or []:
                collect_or_enum_members(c, out)
            return
        # Anything else (ConditionalOperator, CallExpr, MemberExpr,
        # CompoundLiteralExpr, IntegerLiteral, StringLiteral, …) doesn't
        # produce reliable enum-type evidence about the *argument*.
        return


def walk_calls(node, sink):
    if isinstance(node, dict):
        if node.get("kind") == "CallExpr":
            kids = node.get("inner") or []
            if kids:
                callee = first_decl_ref_name(kids[0])
                if callee:
                    for i, arg in enumerate(kids[1:]):
                        members: list[str] = []
                        collect_or_enum_members(arg, members)
                        for m in members:
                            sink(callee, i, m)
        for c in node.get("inner") or []:
            walk_calls(c, sink)
    elif isinstance(node, list):
        for c in node:
            walk_calls(c, sink)


def process_file(path: Path) -> Counter:
    """Run clang on `path`, parse AST, return a Counter of (fname, argpos,
    enum_member) tuples."""
    args = [
        CLANG, "-Xclang", "-ast-dump=json", "-fsyntax-only",
        "-w",                    # suppress warnings
        "-I", str(RAYLIB_SRC),
        str(path),
    ]
    try:
        r = subprocess.run(args, capture_output=True, text=True, timeout=30)
    except subprocess.TimeoutExpired:
        return Counter()
    if not r.stdout:
        return Counter()
    try:
        data = json.loads(r.stdout)
    except json.JSONDecodeError:
        return Counter()

    counter: Counter = Counter()
    def sink(fname, argpos, member):
        counter[(fname, argpos, member)] += 1
    walk_calls(data, sink)
    return counter


def main():
    api = load_api(API_JSON)

    # member -> enum-name (for cross-reference)
    member_to_enum: dict[str, set[str]] = defaultdict(set)
    for e in api["enums"]:
        for m in e["values"]:
            member_to_enum[m["name"]].add(e["name"])

    rlapi_names = {f["name"] for f in api["functions"]}

    sources = list(RAYLIB_EXAMPLES.rglob("*.c")) + list(RAYLIB_SRC.glob("*.c"))
    sources = [p for p in sources if p.name not in {"rglfw.c"}]  # skip GLFW dep
    print(f"scanning {len(sources)} .c files…", file=sys.stderr)

    total: Counter = Counter()
    with ThreadPoolExecutor(max_workers=8) as ex:
        futures = {ex.submit(process_file, p): p for p in sources}
        done = 0
        for fut in as_completed(futures):
            total += fut.result()
            done += 1
            if done % 25 == 0:
                print(f"  …{done}/{len(sources)}", file=sys.stderr)

    # Aggregate per (function, argpos):
    #   member-counts -> enum-counts via member_to_enum.
    by_arg: dict[tuple[str, int], Counter] = defaultdict(Counter)
    for (fname, argpos, member), n in total.items():
        if fname not in rlapi_names:
            continue
        enums = member_to_enum.get(member, set())
        if len(enums) == 1:
            by_arg[(fname, argpos)][next(iter(enums))] += n
        elif len(enums) > 1:
            # Member appears in multiple enums (rare; e.g. CAMERA_*); apportion
            for e in enums:
                by_arg[(fname, argpos)][e] += n / len(enums)

    # Pick the dominant enum per (fname, argpos).
    inferred = []
    for (fname, argpos), tally in sorted(by_arg.items()):
        top, ntop = tally.most_common(1)[0]
        total_calls = sum(tally.values())
        confidence = ntop / total_calls
        if confidence < 0.5 or ntop < 1:
            continue
        inferred.append({
            "function": fname,
            "argpos": argpos,
            "enum": top,
            "confidence": round(confidence, 2),
            "evidence_count": int(ntop),
            "alternatives": {k: int(v) for k, v in tally.items() if k != top},
        })

    # Print table sorted by function name
    print(f"\n{'FUNCTION':<32} {'arg':<4} {'ENUM':<28} {'conf':<6} {'n':<4} alts")
    for r in inferred:
        alts = ", ".join(f"{k}={v}" for k, v in r["alternatives"].items()) if r["alternatives"] else ""
        print(f"{r['function']:<32} {r['argpos']:<4} {r['enum']:<28} {r['confidence']:<6} {r['evidence_count']:<4} {alts}")

    # Also dump a JSON for consumption by gen.py
    outp = Path(__file__).parent / "inferred_enums.json"
    outp.write_text(json.dumps(inferred, indent=2), encoding="utf-8")
    print(f"\nwrote {outp} ({len(inferred)} typed (function, arg) pairs)", file=sys.stderr)


if __name__ == "__main__":
    main()
