#version 150

in vec2 pass_TexCoord;

uniform sampler2D ColorTex;

uniform bool ToggleGrayscale;

out vec4 out_Color;

void main() {
	vec3 tex_Color = texture(ColorTex, pass_TexCoord).rgb;
	out_Color = vec4(tex_Color, 1.0);

    if(ToggleGrayscale){
        float luminance = 0.2126 * tex_Color.r + 0.7152 * tex_Color.g  + 0.0722 * tex_Color.b;
        out_Color = vec4(luminance, luminance, luminance, 1.0);
    }
}
