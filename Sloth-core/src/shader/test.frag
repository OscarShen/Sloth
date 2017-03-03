#version 450 core

in vec2 TexCoord;

uniform sampler2D diffuseMap;

out vec4 out_Color;

void main()
{
	out_Color = texture(diffuseMap, TexCoord);
}
