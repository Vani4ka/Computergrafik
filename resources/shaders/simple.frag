#version 150

in vec3 pass_VertPos;
in vec3 pass_Normal;

in vec3 pass_LightPos;

//diffuse color of planets
in vec3 pass_Color;
vec3 ambientColor = pass_Color;
vec3 specularColor = vec3(1.0f, 1.0f, 1.0f);
float b = 15.0f;

out vec4 out_Color;

void main() {
    vec3 lightDir = pass_LightPos - pass_VertPos;
    vec3 viewDir = -pass_VertPos;
    vec3 halfDir =  normalize(lightDir) + normalize(viewDir);

    float diffuseAngle = dot(normalize(lightDir), normalize(pass_Normal));
    float specularAngle = dot(normalize(pass_Normal), normalize(halfDir));

    vec3 illumination = ambientColor + pass_Color * diffuseAngle + specularColor * pow(specularAngle, b);

    out_Color = vec4(illumination, 1.0);
}
