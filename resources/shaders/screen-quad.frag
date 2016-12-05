#version 150

in vec2 pass_TexCoord;

uniform sampler2D ColorTex;

uniform bool ToggleGrayscale;
uniform bool ToggleMirroringHorizontal;
uniform bool ToggleMirroringVertical;
uniform bool ToggleGaussianBlur;

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

    if(ToggleGaussianBlur){
        vec2 offset = vec2(1.0 / float(textureSize(ColorTex, 0).x));
        color = vec3(0.0,0.0,0.0);

        color += (texture(ColorTex, texCoord + vec2(-offset.x, - offset.y)) * (1.0/16.0)).rgb;
        color += (texture(ColorTex, texCoord + vec2(0, -offset.y)) * (1.0/8.0)).rgb;
        color += (texture(ColorTex, texCoord + vec2(offset.x , -offset.y)) * (1.0/16.0)).rgb;
        color += (texture(ColorTex, texCoord + vec2(-offset.x, 0)) * (1.0/8.0)).rgb;
        color += (texture(ColorTex, texCoord) * (1.0/4.0)).rgb;
        color += (texture(ColorTex, texCoord + vec2(offset.x, 0)) * (1.0/8.0)).rgb;
        color += (texture(ColorTex, texCoord + vec2(-offset.x , offset.y)) * (1.0/16.0)).rgb;
        color += (texture(ColorTex, texCoord + vec2(0, offset.y)) * (1.0/8.0)).rgb;
        color += (texture(ColorTex, texCoord + vec2(offset.x, offset.y)) * (1.0/16.0)).rgb;
    }

    if(ToggleGrayscale){
        float luminance = 0.2126 * color.r + 0.7152 * color.g  + 0.0722 * color.b;
        color = vec3(luminance, luminance, luminance);
    }

    out_Color = vec4(color, 1.0);
}
