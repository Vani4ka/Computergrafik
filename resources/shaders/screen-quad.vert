#version 150
#extension GL_ARB_explicit_attrib_location : require

layout(location = 0) in vec3 in_Position;

out vec2 pass_TexCoord;

void main() {
    vec2 scale = vec2(0.5, 0.5);

	gl_Position = vec4(in_Position, 1.0);
	//transform to [0, 1]
	pass_TexCoord = in_Position.xy * scale + scale;
}
