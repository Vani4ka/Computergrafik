#version 150

in vec3 pass_VertPos;
in vec3 pass_Normal;
in vec2 pass_TexCoord;

//diffuse color of planets
//uniform vec3 DiffuseColor;
uniform vec3 LightPosition;

uniform int ShadingMode;

uniform sampler2D ColorTex;

vec3 ambientColor;
vec3 diffuseColor;
vec3 specularColor = vec3(1.0f, 1.0f, 1.0f);
vec3 borderColor = vec3(0.8, 0.6, 0.0);
float b = 15.0f;

float diffuseMaterial = 1.0f;
float ambientMaterial = 1.0f;
float specularMaterial = 1.0f;

out vec4 out_Color;

void main() {
    diffuseColor = texture(ColorTex, pass_TexCoord).xyz;
    ambientColor = diffuseColor;
    vec3 lightDir = LightPosition - pass_VertPos;
    vec3 viewDir = -pass_VertPos;
    vec3 halfDir =  normalize(lightDir) + normalize(viewDir);

    float diffuseAngle = max(dot(normalize(lightDir), normalize(pass_Normal)), 0.0f);
    float specularAngle = max(dot(normalize(pass_Normal), normalize(halfDir)), 0.0f);

    vec3 illumination = ambientMaterial * ambientColor
        + diffuseMaterial * diffuseColor * diffuseAngle
        + specularMaterial * specularColor * pow(specularAngle, b);

    if(ShadingMode == 1){
        out_Color = vec4(illumination, 1.0);
    }
    //cel shading
    else if(ShadingMode == 2){
        if(dot(normalize(pass_Normal), normalize(viewDir)) > 0.15){
            //no specular light for cel shading for more cartoon-factor
            vec3 celColor = ambientMaterial * ambientColor + diffuseMaterial * diffuseColor * diffuseAngle;
            if(diffuseAngle > 0.96){
                out_Color = vec4(celColor, 1.0);
            }
            else if (diffuseAngle > 0.75){
                out_Color = vec4(celColor * 0.5, 1.0);
            }
            else if (diffuseAngle > 0.5){
                out_Color = vec4(celColor * 0.33, 1.0);
            }
            else if (diffuseAngle > 0.25){
                out_Color = vec4(celColor * 0.25, 1.0);
            }
            else{
                out_Color = vec4(celColor * 0.2, 1.0);
            }
        }
        //border condition
        else{
            out_Color = vec4(diffuseColor,1.0);
        }
    }
}
