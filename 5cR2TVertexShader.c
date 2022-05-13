//vertex coordinates in world space for the render quad
attribute vec3 vertex_worldSpace;
//texture coordinate for this vertex and the render quad
attribute vec2 textureCoordinate_input;

//texture coordinate needs to be passed on to the R2T fragment shader
varying vec2 varyingTextureCoordinate;

//main program for each vertex of the render quad
void main() {
  gl_Position = vec4(vertex_worldSpace, 1.0);
  varyingTextureCoordinate = textureCoordinate_input;
}