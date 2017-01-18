#version 450 core

#define TERRAIN_FIGURE 40.0f

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texCoord;
layout (location = 2) in vec3 normal;

uniform mat4 projection = mat4(1.0f);
uniform mat4 view = mat4(1.0f);
uniform mat4 model = mat4(1.0f);

out DATA {
	vec3 pos;
	vec2 texCoord;
	vec3 normal;
} vs_out;

out vec3 worldPosition;
out vec3 toCameraVector;

void main()
{
	worldPosition = vec3(model * vec4(position, 1.0f));
	gl_Position = projection * view * vec4(worldPosition, 1.0f);
	vs_out.pos = position;
	vs_out.texCoord = texCoord * TERRAIN_FIGURE;
	vs_out.normal = mat3(transpose(inverse(model))) * normal;
	toCameraVector = (inverse(view) * vec4(0.0f,0.0f,0.0f,1.0f)).xyz - worldPosition;
}
