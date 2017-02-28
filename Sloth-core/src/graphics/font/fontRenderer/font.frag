#version 450 core

in vec2 TexCoord;

out vec4 out_Color;

uniform vec3 color;
uniform sampler2D fontAtlas;

void main(void)
{
	out_Color = vec4(color, texture(fontAtlas, TexCoord).a);
}
