#version 450 core

in vec2 TexCoord;

out vec4 out_Color;

uniform vec3 color;
uniform sampler2D fontAtlas;

// ע������ʹ��Ĭ��ֵ��~��ʽʹ��ʱ���Զ�������~
uniform float fontWidth = 0.5f; // ������
uniform float fontEdge = 0.1f; // ����Ľ�����

uniform float borderWidth = 0.7f; // �������������
uniform float borderEdge = 0.1f; // �����������Ľ�����

uniform vec2 offset = vec2(0.0f); // �����ƫ��ֵ�����Բ����������Ӱ

uniform vec3 outlineColor = vec3(1.0f, 0.0f, 0.0f); // ��������������ɫ

void main(void)
{
	// ����
	float distance = 1.0f - texture(fontAtlas, TexCoord).a;
	float alpha = 1.0f - smoothstep(fontWidth, fontWidth + fontEdge, distance);

	// ����������
	float distance2 = 1.0f - texture(fontAtlas, TexCoord + offset).a;
	float outlineAlpha = 1.0f - smoothstep(borderWidth, borderWidth + borderEdge, distance2);

	// ���
	float overallAlpha = alpha + (1.0f - alpha) * outlineAlpha;
	vec3 overallColor = mix(outlineColor, color, alpha / overallAlpha);

	out_Color = vec4(overallColor, overallAlpha);
	//out_Color = vec4(outlineAlpha, outlineAlpha, outlineAlpha, 1.0f);
}
