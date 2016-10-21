#version 150
#extension GL_ARB_explicit_attrib_location : require

layout(location = 2) in vec3 in_Position;
layout(location = 3) in vec3 in_Color;

uniform mat4 ViewMatrix;
uniform mat4 ProjectionMatrix;

out vec3 pass_Color;

void main(void){
    gl_Position = (ProjectionMatrix * ViewMatrix) * vec4(in_Position, 1.0);
    pass_Color = in_Color;
}