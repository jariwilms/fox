#version 460 core

#include "uniform/matrices.unf"

layout(location = 0) in  vec3 a_Position;

layout(location = 0) out vec3 v_TexCoord;

void main()
{
	v_TexCoord = a_Position;
	
	gl_Position = vec4(u_Matrices.projection * mat4(mat3(u_Matrices.view)) * vec4(a_Position, 1.0)).xyww;
}
