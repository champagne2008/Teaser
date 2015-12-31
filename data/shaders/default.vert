#version 330

in layout(location = 0) vec3 v_pos;
in layout(location = 1) vec3 v_col;
in layout(location = 2) vec2 v_uv;

uniform mat4 u_model;
uniform mat4 u_proj;

out vec3 o_col;
out vec2 o_uv;

void main()
{
	gl_Position = u_proj* u_model*vec4(v_pos.xyz,1.0) ;
	o_col = v_col;
	o_uv = v_uv;
}