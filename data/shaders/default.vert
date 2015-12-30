#version 330

in layout(location = 0) vec3 v_pos;
in layout(location = 1) vec3 v_col;
in layout(location = 2) vec2 v_uvs;

uniform mat4 proj;

out vec3 o_col;
out vec2 o_uvs;

void main()
{
	gl_Position =  proj * vec4(v_pos,1.0) ;
	o_col = v_col;
	o_uvs = v_uvs;
}