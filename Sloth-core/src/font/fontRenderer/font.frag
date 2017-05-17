#version 450 core

in vec2 TexCoord;

out vec4 out_Color;

uniform vec3 color;
uniform sampler2D fontAtlas;

// 注意这里使用默认值了~正式使用时请自定义设置~
uniform float fontWidth = 0.5f; // 字体宽度
uniform float fontEdge = 0.1f; // 字体的渐变宽度

uniform float borderWidth = 0.7f; // 字体外轮廓宽度
uniform float borderEdge = 0.1f; // 字体外轮廓的渐变宽度

uniform vec2 offset = vec2(0.0f); // 字体的偏移值，可以产生字体的阴影

uniform vec3 outlineColor = vec3(1.0f, 0.0f, 0.0f); // 字体外轮廓的颜色

void main(void)
{
	// 字体
	float distance = 1.0f - texture(fontAtlas, TexCoord).a;
	float alpha = 1.0f - smoothstep(fontWidth, fontWidth + fontEdge, distance);

	// 字体外轮廓
	float distance2 = 1.0f - texture(fontAtlas, TexCoord + offset).a;
	float outlineAlpha = 1.0f - smoothstep(borderWidth, borderWidth + borderEdge, distance2);

	// 混合
	float overallAlpha = alpha + (1.0f - alpha) * outlineAlpha;
	vec3 overallColor = mix(outlineColor, color, alpha / overallAlpha);

	out_Color = vec4(overallColor, overallAlpha);
	//out_Color = vec4(outlineAlpha, outlineAlpha, outlineAlpha, 1.0f);
}
