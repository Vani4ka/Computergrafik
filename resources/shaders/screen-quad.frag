#version 150

in vec2 pass_TexCoord;

uniform sampler2D ColorTex;

out vec4 out_Color;

void main() {
	out_Color = vec4(texture(ColorTex, pass_TexCoord).rgb,1.0);
//	out_Color = vec4(0.0, 1.0, 0.0, 1.0);
}
