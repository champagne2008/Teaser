#version 330

uniform sampler2D u_sprite;

in vec2 o_uvs;

out vec4 fragColor;

void main(void)
{
	fragColor = texture(u_sprite,o_uvs);
}