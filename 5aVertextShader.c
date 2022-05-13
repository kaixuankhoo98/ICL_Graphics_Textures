//vertex position in world coordinates
attribute vec3 vertex_worldSpace;
//surface normal at the vertex in world coordinates
attribute vec3 normal_worldSpace;
//texture coordinates at that vertex
attribute vec2 textureCoordinate_input;

//model Matrix (Identity in our case)
uniform mat4 mMatrix;
//view Matrix
uniform mat4 vMatrix;
//projection Matrix
uniform mat4 pMatrix;

// ============ added ===============
varying vec2 texture_coord;
uniform vec3 cameraPos;

//main program for each vertex
void main() {
  vec4 vertex_camSpace = vMatrix * mMatrix * vec4(vertex_worldSpace, 1.0);
  gl_Position = pMatrix * vertex_camSpace;
  
  texture_coord = textureCoordinate_input;
}