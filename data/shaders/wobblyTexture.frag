#version 330 core

in vec2 UV;

out vec3 color;

uniform sampler2D renderedTexture;
uniform float time;

vec3 invert(vec3 col)
{
	return vec3(1.0)-col;
}

void main(){
	//color = texture( renderedTexture, UV + 0.005*vec2( sin(time+1024.0*UV.x),cos(time+768.0*UV.y)) ).xyz ;
	color = (texture( renderedTexture, UV ).xyz) ;
}