#version 330

layout(location = 0) in vec3 v_pos;
layout(location = 1) in vec3 v_col;
layout(location = 2) in vec2 v_uv;

uniform mat4 u_model;
uniform mat4 u_proj;
uniform mat4 u_view;

out vec3 o_col;
out vec2 o_uv;

void main()
{
	gl_Position = u_proj * u_view * u_model*vec4(v_pos.xyz,1.0) ;
	o_col = v_col;
	o_uv = v_uv;
}