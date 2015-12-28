#version 330

in layout(location = 0) vec3 v_pos;
in layout(location = 1) vec3 v_col;

out vec3 o_col;

void main()
{
	gl_Position = vec4(v_pos,1.0);
	o_col = v_col;
}