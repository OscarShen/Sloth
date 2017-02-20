#version 450 core

in vec4 clipSpace;
in vec2 texCoord;

uniform sampler2D reflectionTexture;
uniform sampler2D refractionTexture;
uniform sampler2D dudvMap;

// 水波荡漾
uniform float moveFactor;

out vec4 out_Color;

const float waveStrength = 0.02f;

void main(void) {

	// 投影纹理映射获得的ndc坐标，进行了透视除法
	vec2 ndc = (clipSpace.xy / clipSpace.w) / 2.0f + 0.5f;

	vec2 reflectionTexCoord = vec2(ndc.x, -ndc.y);
	vec2 refractionTexCoord = vec2(ndc.x, ndc.y);

	vec2 distortion1 = (texture(dudvMap, vec2(texCoord.x + moveFactor, texCoord.y)).rg * 2.0f - 1.0f) * waveStrength;
	vec2 distortion2 = (texture(dudvMap, vec2(-texCoord.x + moveFactor, texCoord.y + moveFactor)).rg * 2.0f - 1.0f) * waveStrength;
	vec2 totalDistortion = distortion1 + distortion2;

	reflectionTexCoord += totalDistortion;
	reflectionTexCoord.x = clamp(reflectionTexCoord.x, 0.001f, 0.999f);
	reflectionTexCoord.y = clamp(reflectionTexCoord.y, -0.999f, -0.001f);

	refractionTexCoord += totalDistortion;
	refractionTexCoord = clamp(refractionTexCoord, 0.001f, 0.999f);


	vec4 reflectionColor = texture(reflectionTexture, reflectionTexCoord);
	vec4 refractionColor = texture(refractionTexture, refractionTexCoord);

	out_Color = mix(reflectionColor, refractionColor, 0.5f);
	// 增加一点蓝色
	out_Color = mix(out_Color, vec4(0.0f, 0.3f, 0.5f, 1.0f), 0.1f);
}