#version 450 core

in vec2 position;

out vec2 texCoordNow;
out vec2 texCoordNext;
out float blend;

uniform mat4 projection;
uniform mat4 modelView;
uniform vec2 texOffsetNow; // 当前纹理的起始坐标
uniform vec2 texOffsetNext; // 下一纹理的起始坐标
uniform vec2 texCoordInfo; // x表示纹理集的行数， y 表示上述两种坐标的混合参数

void main(void){

	gl_Position = projection * modelView * vec4(position, 0.0, 1.0);

	vec2 texCoord = position + vec2(0.5f, 0.5f);
	texCoord.y = 1.0f - texCoord.y;
	texCoord /= texCoordInfo.x;

	texCoordNow = texCoord + texOffsetNow;
	texCoordNext = texCoord + texOffsetNext;
	blend = texCoordInfo.y;

}