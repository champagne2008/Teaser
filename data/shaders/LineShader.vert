#version 330

layout(location = 0) in vec3 v_pos;

uniform mat4 u_proj;
uniform mat4 u_view;


void main()
{
	gl_Position = u_proj * u_view * vec4(v_pos.xyz,1.0) ;
}