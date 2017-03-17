#version 450 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texCoord;

out vec2 TexCoord;
uniform mat4 model;
uniform mat4 lightSpace;
//uniform mat4 view;
//uniform mat4 projection;

void main()
{
	gl_Position = lightSpace * model * vec4(position, 1.0f);
	TexCoord = texCoord;
}