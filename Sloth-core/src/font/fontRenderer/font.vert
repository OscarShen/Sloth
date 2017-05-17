#version 450 core

layout(location = 0) in vec2 position;
layout(location = 1) in vec2 texCoord;

out vec2 TexCoord;

uniform vec2 model;

void main(void)
{
	gl_Position = vec4(position + model * vec2(2.0f, 2.0f), 0.0f, 1.0f); // model ������ռ��У����Ҫ��2.0ת������Ļ�ռ���
	TexCoord = texCoord;
}