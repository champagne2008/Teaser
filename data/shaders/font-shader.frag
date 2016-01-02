#version 330

uniform sampler2D u_sprite;

uniform vec4 u_color;

in vec2 o_uvs;

out vec4 fragColor;

void main(void)
{
	float sampled = texture(u_sprite,o_uvs).r;
	fragColor= u_color * sampled;
}