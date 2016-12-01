#version 150

in vec2 pass_TexCoord;

uniform sampler2D ColorTex;

uniform bool ToggleGrayscale;
uniform bool ToggleMirroringHorizontal;
uniform bool ToggleMirroringVertical;

out vec4 out_Color;

void main() {
    vec3 color;
    vec2 texCoord = pass_TexCoord;

    vec3 tex_Color = texture(ColorTex, pass_TexCoord).rgb;
    color = tex_Color;

    if(ToggleMirroringHorizontal){
        texCoord = vec2(texCoord.x, abs(texCoord.y - 1));
        tex_Color = texture(ColorTex, texCoord).rgb;
        color = tex_Color;
    }

    if(ToggleMirroringVertical){
        texCoord = vec2(abs(texCoord.x - 1), texCoord.y);
        tex_Color = texture(ColorTex, texCoord).rgb;
        color = tex_Color;
    }

    if(ToggleGrayscale){
        vec3 tex_color = texture(ColorTex, texCoord).rgb;
        float luminance = 0.2126 * tex_color.r + 0.7152 * tex_color.g  + 0.0722 * tex_color.b;
        color = vec3(luminance, luminance, luminance);
    }

    out_Color = vec4(color, 1.0);
}
