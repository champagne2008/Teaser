#version 330

uniform sampler2D tex;

in vec3 o_col;
in vec2 o_uv;

out vec4 fragColor;

void main(void)
{
	fragColor = vec4(o_col,1.0) * texture(tex,o_uv);
}