//for better performance less precision
precision mediump float;

// ============== added ============
// ----- texture ------
varying vec2 texture_coord;
uniform sampler2D texture;
uniform sampler2D normalMap;
//  ----- phong --------
varying vec3 vertexPos; // from vertex shader
varying vec3 vertexNorm; // from vertex shader
uniform vec3 cameraPos;
// from the spec
uniform vec4 ambient;
uniform vec4 diffuse;
uniform vec4 specular;
// constants
#define PI 3.1415926589793238462643383
float k_d = 1.; // diffuse coefficient
float k_s = 0.05; // specular coefficient
float s = 0.5; // heuristic constant
float shininess = 10.;
float phi = 5000.;

//main program for each fragment = pixel candidate
void main() {
  // texture
  vec4 texture_color = texture2D(texture, texture_coord);
  vec3 bumpy = texture2D(normalMap, texture_coord).xyz; // normal in [0,1] range
  bumpy = normalize(bumpy * 2.0 - 1.0); // convert to [-1,1] range

  // from the phong shading
  vec3 norm = bumpy;
  vec3 lightDirection = cameraPos - vertexPos;
  vec3 lightDir_norm = normalize(lightDirection);
  float d = length(lightDirection);
  // ambient
  vec4 ambient_component = ambient;
  // diffuse
  float diff_val = k_d * max(dot(norm, lightDir_norm), 0.0);
  vec4 diffuse_component = diffuse * diff_val;
  // specular
  vec3 reflect = reflect(-lightDir_norm, norm); // reflect about the normal
  vec3 viewDir = cameraPos - vertexPos;
  float spec_val = k_s * pow((max(dot(normalize(viewDir), reflect), 0.0)), shininess);
  vec4 specular_component = specular * spec_val;
  float d_a = phi / (4.0 * PI * (d + s));
  // lighting component to be multiplied by texture
  vec4 lighting = (ambient_component + diffuse_component + specular_component) * d_a;

  // combine and assign
  gl_FragColor = vec4(lighting.rgb * texture_color.rgb, texture_color.a);
}