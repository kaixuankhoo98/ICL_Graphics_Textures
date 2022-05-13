//for better performance less precision
precision mediump float;

// ============== added ============
varying vec2 texture_coord;
uniform sampler2D texture;

//main program for each fragment = pixel candidate
void main() {
  gl_FragColor = texture2D(texture, texture_coord);
}