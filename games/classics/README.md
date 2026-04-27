# Raylib Classics Fasmg Ports

These are first-pass fasm2/fasmg ports of the 12 `raylib-games/classics/src`
games. They default to direct PE x64 DLL builds through:

```asm
include 'raylib_pe64.inc'

; game constants and data...

section '.data' data readable writeable
GLOBSTR.here

section '.text' code readable executable
include 'common.inc'
```

Build from the repository root:

```cmd
cmd /c "call _local.cmd && _build.cmd games\classics\snake.asm"
cmd /c "call _local.cmd && _build.cmd games\classics\*.asm"
```

With no explicit output path, `_build.cmd` builds each EXE beside its source and
copies `raylib.dll` to that same directory.

## Difficulty

| Game | Difficulty | Main reason |
| --- | ---: | --- |
| `snake.c` | 1/5 | Integer grid logic, simple arrays, few APIs |
| `floppy.c` | 1/5 | Simple loops/collision, random tubes |
| `gold_fever.c` | 2/5 | Multiple structs, simple enemy/point logic |
| `arkanoid.c` | 2/5 | Brick matrix, circle/rect collision |
| `asteroids_survival.c` | 3/5 | Vector math, random meteors, triangle drawing |
| `space_invaders.c` | 3/5 | Enemy/shoot arrays and wave state |
| `asteroids.c` | 3/5 | More projectile/meteor splitting state |
| `missile_commander.c` | 4/5 | Mouse input, many arrays, point/circle tests |
| `gorilas.c` | 4/5 | Mouse input, projectile physics, buildings/explosions |
| `pang.c` | 4/5 | Multi-size ball splitting, projectile state, point effects |
| `tetris.c` | 4/5 | 2D matrix transforms and line deletion logic |
| `platformer.c` | 5/5 | Pointer-heavy entity helpers, camera/aggregate ABI issues |

## Porting Rules

- Keep `section` statements visible in each source.
- Place `GLOBSTR.here` explicitly in `.data` and use literal strings at
  Raylib call sites. This keeps constant string bytes out of the code path and
  lets `globstr.inc` fold duplicate/suffix literals.
- Include `common.inc` inside the `.text` section, because it may emit helper
  procedure code.
- In direct PE entry code, set `fastcall.frame = 0`, reserve
  `sub rsp,.space+8`, and define `.space := fastcall.frame` after the entry
  close path so fasm2 tracks one static call-space reservation.
- Keep game state global and source-shaped unless a deviation is documented.
- Use fasm2 `struct` arrays for repeated game objects instead of parallel
  field arrays when the C source has an object-shaped entity.
- Prefer `instance.field` for a single struct instance and pointer iteration
  with `TYPE.field` offsets for arrays.
- Do not pass `r8d`/`r9d` scratch values as later `fastcall` arguments when
  earlier arguments also need those ABI registers; materialize the values in
  memory or non-conflicting registers first.
- Initialize into a waiting state; gameplay updates start only after `GetKeyPressed` reports a key.
- Show keyboard/mouse help only while waiting to start; during active play keep the HUD to score, lives, wave/state text, and game status.
- Prefer scalar Raylib APIs when equivalent; they are easier to audit across x64 ABI boundaries.
- Use `addr` explicitly for larger struct-by-value APIs.
- Use the generated `RayLib` structures where they clarify aggregate layout.
- Use `proc`/`endp` for game-local call targets, and call them with `fastcall` even when they take no arguments. Plain labels are only for the PE entry and local branch targets.
- Declare Win64 nonvolatile registers with `uses` when a routine touches `rbx`, `rsi`, or `rdi`.
- Keep `common.inc` small. One-line aliases are not worth hiding ordinary assembly.

## Shared Helper

`common.inc` provides `TRUE`, `FALSE`, `ClampData`, and shared procedures.
It belongs in the `.text` section of direct PE examples because the shared
procedures may emit code.
The helpers are ordinary fasm2 `proc` bodies, so code generation is gated by
actual use.

`ClampData` intentionally relies on fasm2/fasmg size tracking:

```asm
ClampData playerX, 0, SCREEN_WIDTH-PLAYER_SIZE
xor byte [pauseFlag],1
```

Current common procedures:

| Procedure | Register/argument contract |
| --- | --- |
| `PointInBox` | `fastcall PointInBox, x, y, left, top, right, bottom`; returns `eax = TRUE/FALSE`. |
| `RectsOverlap` | `fastcall RectsOverlap, x1, y1, w1, h1, x2, y2, w2, h2`; returns `eax = TRUE/FALSE`. |
| `CircleRectOverlap` | `fastcall CircleRectOverlap, x, y, radius, left, top, width, height`; closest-point circle/rect test, returns `eax = TRUE/FALSE`. |

## API Layer Findings

- PE examples now include `raylib_imports_pe.inc` directly in `.idata`; the `RayLibImportTable` macro was removed.
- Global enum aliases such as `FLAG_VSYNC_HINT` and `KEY_R` were removed. Naked enum tokens still work at typed Raylib call sites through `transform`, but outside those calls the user must write the namespaced form.
- `define RayLib` now anchors the namespace so `RayLib.API` and `sizeof.RayLib.*` resolve correctly from nested contexts.
- Enum namespaces are anchored as well, for example `define ConfigFlags ConfigFlags`; this lets `transform value, RayLib.ConfigFlags` resolve `FLAG_WINDOW_RESIZABLE`.
- Color parameters now transform through `RayLib`, so typed calls can use `ClearBackground RAYWHITE`; outside typed calls keep the namespaced form, for example `RayLib.RAYWHITE`.
- `RLAPI` now emits calls with escaped namespace components, for example `fastcall [=RayLib=.=API.function], arguments`.
- Raylib `bool` returns are left in `al`; examples test `al` instead of `eax`.
- `tests\fasm2\proc_namespace_raylib.asm` verifies Raylib calls from inside a fasm2 `proc`.
- `tests\fasm2\namespace_transform_anchor.asm` directly tests a local `calminstruction` using `transform value, RayLib.ConfigFlags`.
- The classics use fasm2 `proc` plus caller-side `fastcall` for nested call targets. This keeps Win64 shadow space/alignment handling in the fasm2 ABI layer, and routines that use nonvolatile registers make the save/restore contract explicit through `uses`.
- `RAYLIB_DEBUG` can wrap `RLAPI` in the PE64 include to break if `rsp` is misaligned after a Raylib ABI call. The current classics pass the normal build and launch smoke with the ABI-procedure structure in place.
- Generated Raylib structs now use explicit Win32/Win64 C ABI padding. Raylib's public headers do not pack these structs. Single nested Raylib struct fields use typed fasm2 fields such as `position RayLib.Vector3`; arrays of nested structs still use raw `rb count*sizeof.RayLib.Type` storage.
- `tests\fasm2\struct_layout64.asm` and `tests\fasm2\struct_layout32.asm` assert representative offsets and sizes against the compiler-observed C layout.

## Aggregate Checklist

| API | Current rule |
| --- | --- |
| `GetMousePosition` | Return is an 8-byte `Vector2`; store with `mov [mousePos], rax`. |
| Mouse coordinates for scalar APIs | `GetMousePosition` fields are floats; convert with `cvttss2si` before using them as `DrawLine`/physics integer coordinates. |
| `DrawCircleV` / `DrawTriangle` | `Vector2` is 8 bytes and can be passed from qword memory, e.g. `[mousePos]`. |
| `Fade` | Return is packed `Color` in `eax`; store with `mov [fadeColor], eax`. |
| `DrawRectangleRec` | Use `DrawRectangleRec addr rect, color`. |
| `CheckCollisionRecs` | Use `CheckCollisionRecs addr rec1, addr rec2`; test the result in `al`. |
| `BeginMode2D` | Use `BeginMode2D addr camera`; `Camera2D` is larger than 8 bytes. |
| Float radius APIs | Pass IEEE float data, e.g. `float dword 18.0` or `float dword [radiusF]`, not integer bit patterns. |

## Per-Game Notes

| Game | APIs and notes | Status and gaps |
| --- | --- | --- |
| `snake.asm` | Keyboard, random, rectangles, text, `SNAKE_SEGMENT` struct array | Source-shaped grid port. Growth now initializes the new tail segment instead of exposing uninitialized upper-left data. Launch smoke passed. |
| `floppy.asm` | Keyboard, random, circles, rectangles, `TextFormat`, `TUBE` struct array | Migrated closer to the C source: 100 fixed tube pairs, 24 px bird at x=80, held-key vertical motion, source tube dimensions, pass scoring, hi-score, and one-frame pass flash. Collision now uses closest-point circle/rect geometry with a slightly smaller hit radius so corner hits match the drawn bird better. Launch smoke passed. |
| `gold_fever.asm` | Keyboard, random, rectangles, circles, `ClampData`, `TextFormat` | Restored follow/home loop, enemy patrol/chase radius, source start positions and player speed, point/home placement range, score/hi-score text, and stepped enemy speed increase. Launch smoke passed. |
| `arkanoid.asm` | Keyboard, circle/rect drawing, brick matrix | Migrated to the source 20-column brick layout, source gray/dark-gray checker bricks, 80 px paddle, 7 px ball, launch state, paddle influence, and lives. Uses manual scalar collision. Launch smoke passed. |
| `asteroids_survival.asm` | Keyboard, random, circles, `DrawTriangle`, `RayLib.Vector2`, `METEOR` struct array | Ship triangle vertices are stored as real `Vector2` floats; meteor radii have float mirrors. Initial meteor placement excludes a 150 px player spawn zone. The ship now keeps the last nonzero arrow-key movement vector and points in that direction, including diagonals. Launch smoke passed. |
| `space_invaders.asm` | Keyboard, `ENEMY`/`SHOT` struct arrays, rectangles, `RectsOverlap`, `Fade`, `MeasureText`, `TextFormat` | Restored first/second/third wave sizes, 50-enemy pool, 50-shot pool, hold-to-fire cadence, score, shared rectangle collision, and fade-in/fade-out wave text. Launch smoke passed. |
| `asteroids.asm` | Keyboard, directional projectiles, `METEOR`/`SHOOT` struct arrays, x87 trig, `DrawTriangle`, scalar `DrawLine`, `RayLib.Vector2` | Ship rotation, acceleration, movement, shot direction, wrapping, and triangle vertices now use x87 `fsin`/`fcos` from a degree angle. Initial placement excludes a 150 px spawn zone, and meteors split large-to-medium-to-small. The ship fill uses counter-clockwise triangle order, with scalar hull lines and a center dot as a visibility fallback. Launch smoke passed. |
| `missile_commander.asm` | Mouse, `MISSILE`/`INTERCEPTOR`/`EXPLOSION`/`LAUNCHER` struct arrays, `RayLib.Vector2`, `TextFormat` | Left-click converts mouse `Vector2` floats to integer targets, launches from active launchers, scores intercepted missiles, destroys launchers/cities, and ends when either all launchers or all cities are lost. Launch smoke passed. |
| `gorilas.asm` | Mouse targeting, fixed-point projectile physics, variable skyline, `BUILDING`/`PLAYER`/`CRATER` struct arrays, `RayLib.Vector2` | Reworked toward the source model: 15 variable-width/color buildings, 40x40 players placed on rooftops, previous/current aim triangles, 10 px projectile, 8.8 fixed-point velocity with source-like gravity, player death, and persistent crater holes that shots pass through. Current aim color is held in a nonvolatile register across the previous-aim draw call. A defeated player now records an explicit winner and displays blue/red win text. Player hitbox coordinates are materialized before the shared circle/rect helper call so ABI argument setup cannot clobber them. Launch smoke passed. |
| `pang.asm` | Keyboard, harpoon, bouncing balls, `BALL`/`POINT_LABEL` struct arrays, `TextFormat` | Starts with two big balls; harpoon collision uses each ball radius, balls split down to small size, and score is awarded by ball size. Bounce impulse is radius-aware, player hits use circle/rect collision, and hit score labels animate upward. Launch smoke passed. |
| `tetris.asm` | Grid matrix, fading line clear, keyboard, `TextFormat` | Active piece now uses a 4x4 tetromino mask table with seven piece families, rotation, next-piece preview, level display, level-based drop speed, delayed FADING row deletion, and source-style wall/bottom `BLOCK` boundary cells. Launch smoke passed. |
| `platformer.asm` | Keyboard, tile map, `Camera2D`, coins, score | Reworked around the source 20x12 tile map, 2x camera scale, border/platform block layout, source coin positions, centered score text, tile collision, and 8.8 fixed-point horizontal acceleration/deceleration, gravity, jump impulse, terminal fall speed, and jump release. Launch smoke passed. |

## Helper Test

`tests\aggregate_smoke.asm` builds a tiny PE x64 DLL example that exercises
`RayLib.Vector2`, `RayLib.Rectangle`, `RayLib.Color`, `RayLib.Camera2D`,
`GetMousePosition`, `Fade`, `TextFormat`, `DrawRectangleRec`,
`CheckCollisionRecs`, `BeginMode2D`, and `DrawCircleV`.

Build it with:

```cmd
cmd /c "call _local.cmd && _build.cmd games\classics\tests\aggregate_smoke.asm"
```

## Build And Smoke Status

All 12 games and the aggregate smoke source assembled as direct PE x64 DLL examples.
The current source form was also compile-verified with explicit outputs under
`%TEMP%\fasmg_raylib_classics_verify`, which avoids overwriting any running
source-adjacent EXEs during interactive testing.

All 12 games now draw their initial scene but hold gameplay updates until any key is pressed. Restart goes through `InitGame`, so restarted games wait again before moving.

| Target | EXE size | Launch smoke |
| --- | ---: | --- |
| `snake.exe` | 3584 | Stayed alive for 2 seconds, closed |
| `floppy.exe` | 3584 | Stayed alive for 2 seconds, closed |
| `gold_fever.exe` | 4096 | Stayed alive for 2 seconds, closed |
| `arkanoid.exe` | 4096 | Stayed alive for 2 seconds, closed |
| `asteroids_survival.exe` | 4096 | Stayed alive for 2 seconds, closed |
| `space_invaders.exe` | 4608 | Stayed alive for 2 seconds, closed |
| `asteroids.exe` | 6144 | Stayed alive for 2 seconds, closed |
| `missile_commander.exe` | 5120 | Stayed alive for 2 seconds, closed |
| `gorilas.exe` | 7168 | Stayed alive for 2 seconds, closed |
| `pang.exe` | 4096 | Stayed alive for 2 seconds, closed |
| `tetris.exe` | 5632 | Stayed alive for 2 seconds, closed |
| `platformer.exe` | 5120 | Stayed alive for 2 seconds, closed |
| `aggregate_smoke.exe` | 2560 | Stayed alive for 2 seconds, closed |

Interactive smoke testing is still pending: controls, pause/restart, score/win/game-over paths, and edge cases should be validated manually.

## Remaining Work

- `platformer.asm` now uses the source tile map, camera scale, and fixed-point movement. It still does not mirror the C source's pointer-based `Entity` helper API one-for-one, but the gameplay mechanics are much closer.
- `asteroids.asm` now uses x87 trigonometry for rotation/movement/drawing instead of lookup tables. Further parity work would be tuning constants against the C version rather than changing the approach.
- `gorilas.asm` now follows the original turn/projectile shape more closely, but it uses direct mouse-vector fixed-point ball speed instead of computing angle/power through trig. If target hits still feel unreliable in testing, the next likely adjustment is collision tolerance or swept collision around the rooftop players rather than another rendering change.
- Remaining raw `dup` arrays are single-field grids, flags, or heights rather than parallel object fields.
- Decide whether arrays of namespaced fasm2 `struct` fields deserve a deeper API-layer abstraction or should remain raw-size fields.
- Add focused tests for more `TextFormat` vararg combinations and any additional aggregate APIs used by deeper ports.
- Perform user-side interactive smoke testing and record results in the per-game table.
