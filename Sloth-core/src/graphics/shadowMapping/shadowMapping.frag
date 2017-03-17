#version 450 core

in vec2 TexCoord;

uniform sampler2D modelTexture;
void main()
{
	float alpha = texture(modelTexture, TexCoord).a;
	if(alpha < 0.5f)
		discard;
}