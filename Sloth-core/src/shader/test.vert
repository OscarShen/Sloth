#version 450 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texCoord;

uniform mat4 projection = mat4(1.0f);
uniform mat4 view = mat4(1.0f);
uniform mat4 model = mat4(1.0f);

out vec2 TexCoord;

void main()
{
	gl_Position = projection * view * model * vec4(position, 1.0f);
	TexCoord = texCoord;
}
