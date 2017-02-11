#version 450 core

// ����������lowerLimit �� higher Limit��
// ���� higherLimit �Ĳ�����ȫ��ʾ��պУ�
// ���� lowerLimit �Ĳ�����ȫ��ʾ fog, 
// �м䲿�ֲ������߲�ֵ��������ֵ����պе� size �й�
#define HIGH_LIMIT 40.0f
#define LOW_LIMIT 0.0f

in vec3 texCoords;
out vec4 out_Color;

// ������ɫ
uniform vec3 fogColor;

uniform samplerCube cubeMap;

void main(void){
	// ��� LOW_LIMIT ȡ������LOW_LIMIT ���� fogFactor = 0.0f�� HIGH_LIMIT ���� fogFactor = 1.0f
	float fogFactor = (texCoords.y - LOW_LIMIT) / (HIGH_LIMIT - LOW_LIMIT);
	// ������ 0.0f �� 1.0f
	fogFactor = clamp(fogFactor, 0.0f, 1.0f);

    out_Color = mix(vec4(fogColor, 1.0f), texture(cubeMap, texCoords), fogFactor);
}