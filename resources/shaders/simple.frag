#version 150

in vec3 pass_Color;

in  vec3 pass_Normal;
out vec4 out_Color;

void main() {
  out_Color = vec4(pass_Color, 1.0);
}
