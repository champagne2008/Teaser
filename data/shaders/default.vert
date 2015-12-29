#version 330

in layout(location = 0) vec3 v_pos;
in layout(location = 1) vec3 v_col;


uniform mat4 u_translation;
out vec3 o_col;

void main()
{
	gl_Position = u_translation*vec4(v_pos,1.0);
	o_col = v_col;
}