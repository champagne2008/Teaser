#version 330

layout(location = 0)in  vec2 v_pos;
layout(location = 1)in  vec2 v_uvs;

uniform mat4 u_model;
uniform mat4 u_proj;

out vec2 o_uvs;

void main()
{
	gl_Position = u_proj* u_model * vec4(v_pos,0.0,1.0) ;
	o_uvs = v_uvs;
}