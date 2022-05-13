precision mediump float;

//a texture sampling unit, which is bound to the render quad texture buffer
uniform sampler2D textureRendered;

//texture coordinates coming from the vertex shader, interpolated through the rasterizer
varying vec2 varyingTextureCoordinate;

//main program for each fragment of the render quad
void main() {
  
  float s[12];
  s[0] = -0.10568; s[1] = -0.07568; s[2] = -0.042158;
  s[3] = -0.02458; s[4] = -0.01987456; s[5] = -0.0112458;
  s[6] = 0.0112458; s[7] = 0.01987456; s[8] = 0.02458;
  s[9] = 0.042158; s[10] = 0.07568; s[11] = 0.10568;
  float d_max = 0.3;

  // calculate p_norm
  vec2 p_norm = normalize(vec2(0.5,0.5) - varyingTextureCoordinate);

  vec3 rgb_blur;
  for (int i = 0; i <= 11; ++i) {
    float d_i = s[i]*d_max;
    vec4 sum = texture2D(textureRendered, ((varyingTextureCoordinate) + (p_norm) * d_i));
    rgb_blur = rgb_blur + sum.rgb; 
  }
  rgb_blur = rgb_blur / 12.;

  gl_FragColor = vec4(rgb_blur,1.0);
}