#version 330


uniform unsigned int u_time;
in vec3 o_col;
out vec4 fragColor;

void main(void)
{
	fragColor = vec4(o_col,(sin(u_time*0.005)+1)/2) ;
}