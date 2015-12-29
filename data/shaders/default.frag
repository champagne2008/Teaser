#version 330

in vec3 o_col;
out vec4 fragColor;

void main(void)
{
	fragColor = vec4(o_col,1) ;
}