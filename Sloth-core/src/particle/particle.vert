#version 450 core

layout(location = 0) in vec2 position;
layout(location = 1) in mat4 modelView;
layout(location = 5) in vec4 texOffsets;
layout(location = 6) in float blendFactor;

out vec2 texCoordNow;
out vec2 texCoordNext;
out float blend;

uniform mat4 projection;
uniform float numberOfRows;

void main(void){

	gl_Position = projection * modelView * vec4(position, 0.0, 1.0);

	vec2 texCoord = position + vec2(0.5f, 0.5f);
	texCoord.y = 1.0f - texCoord.y;
	texCoord /= numberOfRows;

	texCoordNow = texCoord + texOffsets.xy;
	texCoordNext = texCoord + texOffsets.zw;
	blend = blendFactor;

}