#version 450 core

layout(location = 0) in vec2 position;
layout(location = 1) in vec2 texCoord;

out vec2 TexCoord;

uniform mat4 transformationMatrix;

void main()
{
	gl_Position = transformationMatrix * vec4(position, 0.0f, 1.0f);
	TexCoord = texCoord;
}