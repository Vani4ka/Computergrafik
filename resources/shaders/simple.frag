#version 150

in vec3 pass_VertPos;
in vec3 pass_Normal;

in vec3 pass_LightPos;

//diffuse color of planets
in vec3 pass_Color;
vec3 ambientColor = pass_Color;
vec3 specularColor = vec3(1.0f, 1.0f, 1.0f);

out vec4 out_Color;

void main() {
  out_Color = vec4(pass_Color, 1.0);
}
