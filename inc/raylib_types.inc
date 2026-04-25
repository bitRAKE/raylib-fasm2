; raylib structs — generated; do not edit by hand
;
; A handful of C field names collide with fasmg directives or with
; macros pulled in by the Win64 framework (pe.inc, proc64.inc).
; Affected fields are renamed with a trailing underscore:
;   data -> data_
;   format -> format_
;   frame -> frame_

; Vector2, 2 components
struct Vector2
  x  dd ?  ; Vector x component
  y  dd ?  ; Vector y component
ends

; Vector3, 3 components
struct Vector3
  x  dd ?  ; Vector x component
  y  dd ?  ; Vector y component
  z  dd ?  ; Vector z component
ends

; Vector4, 4 components
struct Vector4
  x  dd ?  ; Vector x component
  y  dd ?  ; Vector y component
  z  dd ?  ; Vector z component
  w  dd ?  ; Vector w component
ends

; Matrix, 4x4 components, column major, OpenGL style, right-handed
struct Matrix
  m0   dd ?  ; Matrix first row (4 components)
  m4   dd ?  ; Matrix first row (4 components)
  m8   dd ?  ; Matrix first row (4 components)
  m12  dd ?  ; Matrix first row (4 components)
  m1   dd ?  ; Matrix second row (4 components)
  m5   dd ?  ; Matrix second row (4 components)
  m9   dd ?  ; Matrix second row (4 components)
  m13  dd ?  ; Matrix second row (4 components)
  m2   dd ?  ; Matrix third row (4 components)
  m6   dd ?  ; Matrix third row (4 components)
  m10  dd ?  ; Matrix third row (4 components)
  m14  dd ?  ; Matrix third row (4 components)
  m3   dd ?  ; Matrix fourth row (4 components)
  m7   dd ?  ; Matrix fourth row (4 components)
  m11  dd ?  ; Matrix fourth row (4 components)
  m15  dd ?  ; Matrix fourth row (4 components)
ends

; Color, 4 components, R8G8B8A8 (32bit)
struct Color
  r  db ?  ; Color red value
  g  db ?  ; Color green value
  b  db ?  ; Color blue value
  a  db ?  ; Color alpha value
ends

; Rectangle, 4 components
struct Rectangle
  x       dd ?  ; Rectangle top-left corner position x
  y       dd ?  ; Rectangle top-left corner position y
  width   dd ?  ; Rectangle width
  height  dd ?  ; Rectangle height
ends

; Image, pixel data stored in CPU memory (RAM)
struct Image
  data_    dq ?  ; Image raw data  ; renamed from `data`
  width    dd ?  ; Image base width
  height   dd ?  ; Image base height
  mipmaps  dd ?  ; Mipmap levels, 1 by default
  format_  dd ?  ; Data format (PixelFormat type)  ; renamed from `format`
ends

; Texture, tex data stored in GPU memory (VRAM)
struct Texture
  id       dd ?  ; OpenGL texture id
  width    dd ?  ; Texture base width
  height   dd ?  ; Texture base height
  mipmaps  dd ?  ; Mipmap levels, 1 by default
  format_  dd ?  ; Data format (PixelFormat type)  ; renamed from `format`
ends

; RenderTexture, fbo for texture rendering
struct RenderTexture
  id       dd ?  ; OpenGL framebuffer object id
  texture  Texture  ; Color buffer attachment texture
  depth    Texture  ; Depth buffer attachment texture
ends

; NPatchInfo, n-patch layout info
struct NPatchInfo
  source  Rectangle  ; Texture source rectangle
  left    dd ?  ; Left border offset
  top     dd ?  ; Top border offset
  right   dd ?  ; Right border offset
  bottom  dd ?  ; Bottom border offset
  layout  dd ?  ; Layout of the n-patch: 3x3, 1x3 or 3x1
ends

; GlyphInfo, font characters glyphs info
struct GlyphInfo
  value     dd ?  ; Character value (Unicode)
  offsetX   dd ?  ; Character offset X when drawing
  offsetY   dd ?  ; Character offset Y when drawing
  advanceX  dd ?  ; Character advance position X
  image     Image  ; Character image data
ends

; Font, font texture and GlyphInfo array data
struct Font
  baseSize      dd ?  ; Base size (default chars height)
  glyphCount    dd ?  ; Number of glyph characters
  glyphPadding  dd ?  ; Padding around the glyph characters
  texture       Texture  ; Texture atlas containing the glyphs
  recs          dq ?  ; Rectangles in texture for the glyphs
  glyphs        dq ?  ; Glyphs info data
ends

; Camera, defines position/orientation in 3d space
struct Camera3D
  position    Vector3  ; Camera position
  target      Vector3  ; Camera target it looks-at
  up          Vector3  ; Camera up vector (rotation over its axis)
  fovy        dd ?  ; Camera field-of-view aperture in Y (degrees) in perspective, used as near plane height in world units in orthographic
  projection  dd ?  ; Camera projection: CAMERA_PERSPECTIVE or CAMERA_ORTHOGRAPHIC
ends

; Camera2D, defines position/orientation in 2d space
struct Camera2D
  offset    Vector2  ; Camera offset (screen space offset from window origin)
  target    Vector2  ; Camera target (world space target point that is mapped to screen space offset)
  rotation  dd ?  ; Camera rotation in degrees (pivots around target)
  zoom      dd ?  ; Camera zoom (scaling around target), must not be set to 0, set to 1.0f for no scale
ends

; Mesh, vertex data and vao/vbo
struct Mesh
  vertexCount    dd ?  ; Number of vertices stored in arrays
  triangleCount  dd ?  ; Number of triangles stored (indexed or not)
  vertices       dq ?  ; Vertex position (XYZ - 3 components per vertex) (shader-location = 0)
  texcoords      dq ?  ; Vertex texture coordinates (UV - 2 components per vertex) (shader-location = 1)
  texcoords2     dq ?  ; Vertex texture second coordinates (UV - 2 components per vertex) (shader-location = 5)
  normals        dq ?  ; Vertex normals (XYZ - 3 components per vertex) (shader-location = 2)
  tangents       dq ?  ; Vertex tangents (XYZW - 4 components per vertex) (shader-location = 4)
  colors         dq ?  ; Vertex colors (RGBA - 4 components per vertex) (shader-location = 3)
  indices        dq ?  ; Vertex indices (in case vertex data comes indexed)
  boneCount      dd ?  ; Number of bones (MAX: 256 bones)
  _pad0          rb 4
  boneIndices    dq ?  ; Vertex bone indices, up to 4 bones influence by vertex (skinning) (shader-location = 6)
  boneWeights    dq ?  ; Vertex bone weight, up to 4 bones influence by vertex (skinning) (shader-location = 7)
  animVertices   dq ?  ; Animated vertex positions (after bones transformations)
  animNormals    dq ?  ; Animated normals (after bones transformations)
  vaoId          dd ?  ; OpenGL Vertex Array Object id
  _pad1          rb 4
  vboId          dq ?  ; OpenGL Vertex Buffer Objects id (default vertex data)
ends

; Shader
struct Shader
  id    dd ?  ; Shader program id
  _pad0  rb 4
  locs  dq ?  ; Shader locations array (RL_MAX_SHADER_LOCATIONS)
ends

; MaterialMap
struct MaterialMap
  texture  Texture  ; Material map texture
  color    Color  ; Material map color
  value    dd ?  ; Material map value
ends

; Material, includes shader and maps
struct Material
  shader  Shader  ; Material shader
  maps    dq ?  ; Material maps array (MAX_MATERIAL_MAPS)
  params  dd ?,?,?,?  ; Material generic parameters (if required)
ends

; Transform, vertex transformation data
struct Transform
  translation  Vector3  ; Translation
  rotation     Vector4  ; Rotation
  scale        Vector3  ; Scale
ends

; Bone, skeletal animation bone
struct BoneInfo
  name    db ?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?  ; Bone name
  parent  dd ?  ; Bone parent
ends

; Skeleton, animation bones hierarchy
struct ModelSkeleton
  boneCount  dd ?  ; Number of bones
  _pad0      rb 4
  bones      dq ?  ; Bones information (skeleton)
  bindPose   dq ?  ; Bones base transformation (Transform[])
ends

; Model, meshes, materials and animation data
struct Model
  transform      Matrix  ; Local transform matrix
  meshCount      dd ?  ; Number of meshes
  materialCount  dd ?  ; Number of materials
  meshes         dq ?  ; Meshes array
  materials      dq ?  ; Materials array
  meshMaterial   dq ?  ; Mesh material number
  skeleton       ModelSkeleton  ; Skeleton for animation
  currentPose    dq ?  ; Current animation pose (Transform[])
  boneMatrices   dq ?  ; Bones animated transformation matrices
ends

; ModelAnimation, contains a full animation sequence
struct ModelAnimation
  name           db ?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?  ; Animation name
  boneCount      dd ?  ; Number of bones (per pose)
  keyframeCount  dd ?  ; Number of animation key frames
  keyframePoses  dq ?  ; Animation sequence keyframe poses [keyframe][pose]
ends

; Ray, ray for raycasting
struct Ray
  position   Vector3  ; Ray position (origin)
  direction  Vector3  ; Ray direction (normalized)
ends

; RayCollision, ray hit information
struct RayCollision
  hit       db ?  ; Did the ray hit something?
  _pad0     rb 3
  distance  dd ?  ; Distance to the nearest hit
  point     Vector3  ; Point of the nearest hit
  normal    Vector3  ; Surface normal of hit
ends

; BoundingBox
struct BoundingBox
  min  Vector3  ; Minimum vertex box-corner
  max  Vector3  ; Maximum vertex box-corner
ends

; Wave, audio wave data
struct Wave
  frameCount  dd ?  ; Total number of frames (considering channels)
  sampleRate  dd ?  ; Frequency (samples per second)
  sampleSize  dd ?  ; Bit depth (bits per sample): 8, 16, 32 (24 not supported)
  channels    dd ?  ; Number of channels (1-mono, 2-stereo, ...)
  data_       dq ?  ; Buffer data pointer  ; renamed from `data`
ends

; AudioStream, custom audio stream
struct AudioStream
  buffer      dq ?  ; Pointer to internal data used by the audio system
  processor   dq ?  ; Pointer to internal data processor, useful for audio effects
  sampleRate  dd ?  ; Frequency (samples per second)
  sampleSize  dd ?  ; Bit depth (bits per sample): 8, 16, 32 (24 not supported)
  channels    dd ?  ; Number of channels (1-mono, 2-stereo, ...)
  _pad0       rb 4
ends

; Sound
struct Sound
  stream      AudioStream  ; Audio stream
  frameCount  dd ?  ; Total number of frames (considering channels)
  _pad0       rb 4
ends

; Music, audio stream, anything longer than ~10 seconds should be streamed
struct Music
  stream      AudioStream  ; Audio stream
  frameCount  dd ?  ; Total number of frames (considering channels)
  looping     db ?  ; Music looping enable
  _pad0       rb 3
  ctxType     dd ?  ; Type of music context (audio filetype)
  _pad1       rb 4
  ctxData     dq ?  ; Audio context data, depends on type
ends

; VrDeviceInfo, Head-Mounted-Display device parameters
struct VrDeviceInfo
  hResolution             dd ?  ; Horizontal resolution in pixels
  vResolution             dd ?  ; Vertical resolution in pixels
  hScreenSize             dd ?  ; Horizontal size in meters
  vScreenSize             dd ?  ; Vertical size in meters
  eyeToScreenDistance     dd ?  ; Distance between eye and display in meters
  lensSeparationDistance  dd ?  ; Lens separation distance in meters
  interpupillaryDistance  dd ?  ; IPD (distance between pupils) in meters
  lensDistortionValues    dd ?,?,?,?  ; Lens distortion constant parameters
  chromaAbCorrection      dd ?,?,?,?  ; Chromatic aberration correction parameters
ends

; VrStereoConfig, VR stereo rendering configuration for simulator
struct VrStereoConfig
  projection         rb 2*sizeof.Matrix  ; VR projection matrices (per eye)
  viewOffset         rb 2*sizeof.Matrix  ; VR view offset matrices (per eye)
  leftLensCenter     dd ?,?  ; VR left lens center
  rightLensCenter    dd ?,?  ; VR right lens center
  leftScreenCenter   dd ?,?  ; VR left screen center
  rightScreenCenter  dd ?,?  ; VR right screen center
  scale              dd ?,?  ; VR distortion scale
  scaleIn            dd ?,?  ; VR distortion scale in
ends

; File path list
struct FilePathList
  count  dd ?  ; Filepaths entries count
  _pad0  rb 4
  paths  dq ?  ; Filepaths entries
ends

; Automation event
struct AutomationEvent
  frame_  dd ?  ; Event frame  ; renamed from `frame`
  type    dd ?  ; Event type (AutomationEventType)
  params  dd ?,?,?,?  ; Event parameters (if required)
ends

; Automation event list
struct AutomationEventList
  capacity  dd ?  ; Events max entries (MAX_AUTOMATION_EVENTS)
  count     dd ?  ; Events entries count
  events    dq ?  ; Events entries
ends
