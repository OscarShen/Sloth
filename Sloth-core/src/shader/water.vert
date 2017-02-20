#version 450 core

layout(location = 0) in vec2 position;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

out vec4 clipSpace;
out vec2 texCoord;

const float tiling = 6.0f;

void main(void) {

	clipSpace = projection * view * model * vec4(position.x, 0.0, position.y, 1.0);
	gl_Position = clipSpace;
	texCoord = vec2(position.x / 2.0f + 0.5f, position.y / 2.0f + 0.5f);
}