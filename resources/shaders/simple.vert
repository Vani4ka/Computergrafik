#version 150
#extension GL_ARB_explicit_attrib_location : require
// vertex attributes of VAO
layout(location = 0) in vec3 in_Position;
layout(location = 1) in vec3 in_Normal;
layout(location = 2) in vec2 in_Texcoord;
layout(location = 3) in vec3 in_Tangent;

//Matrix Uniforms as specified with glUniformMatrix4fv
uniform mat4 ModelMatrix;
uniform mat4 ViewMatrix;
uniform mat4 ProjectionMatrix;
uniform mat4 NormalMatrix;

out vec3 pass_Normal;
out vec3 pass_VertPos;
out vec2 pass_TexCoord;
out vec3 pass_Tangent;
out vec3 pass_Bitangent;

void main(void)
{
	gl_Position = (ProjectionMatrix  * ViewMatrix * ModelMatrix) * vec4(in_Position, 1.0);

	vec4 homoVertPos = ViewMatrix * ModelMatrix * vec4(in_Position, 1.0);

	//Convert to euclidean coordinates
	pass_VertPos = (homoVertPos / homoVertPos.w).xyz;

	pass_TexCoord = in_Texcoord;

	pass_Bitangent = cross(in_Normal, in_Tangent);

    pass_Normal =  (NormalMatrix * vec4(in_Normal, 0.0)).xyz;
	pass_Tangent = (NormalMatrix * vec4(in_Tangent, 1.0)).xyz;
	pass_Bitangent = (NormalMatrix * vec4(pass_Bitangent, 1.0)).xyz;
}
