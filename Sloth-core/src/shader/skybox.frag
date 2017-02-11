#version 450 core

// 定义两个量lowerLimit 和 higher Limit，
// 高于 higherLimit 的部分完全显示天空盒，
// 低于 lowerLimit 的部分完全显示 fog, 
// 中间部分采用两者插值。这两个值和天空盒的 size 有关
#define HIGH_LIMIT 40.0f
#define LOW_LIMIT 0.0f

in vec3 texCoords;
out vec4 out_Color;

// 雾气颜色
uniform vec3 fogColor;

uniform samplerCube cubeMap;

void main(void){
	// 相对 LOW_LIMIT 取参数，LOW_LIMIT 处的 fogFactor = 0.0f， HIGH_LIMIT 处的 fogFactor = 1.0f
	float fogFactor = (texCoords.y - LOW_LIMIT) / (HIGH_LIMIT - LOW_LIMIT);
	// 限制在 0.0f 到 1.0f
	fogFactor = clamp(fogFactor, 0.0f, 1.0f);

    out_Color = mix(vec4(fogColor, 1.0f), texture(cubeMap, texCoords), fogFactor);
}