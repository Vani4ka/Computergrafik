#version 150
#extension GL_ARB_explicit_attrib_location : require

layout(location = 4) in vec3 in_Position;

uniform mat4 ViewMatrix;
uniform mat4 ProjectionMatrix;
uniform mat4 ModelMatrix;

out vec3 pass_Color;

void main(void){
    gl_Position = (ProjectionMatrix * ViewMatrix * ModelMatrix) * vec4(in_Position, 1.0);
    pass_Color = vec3(1.0, 1.0, 1.0);
}
