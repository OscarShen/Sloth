#version 450 core

// ���ƹ���
#define MAX_LIGHT 4
in vec3 worldPosition;
in vec3 toCameraVector;
in float visibility;
in vec2 TexCoord;
in vec3 Normal;

uniform sampler2D diffuseMap;
uniform sampler2D specularMap;
uniform float useSpecularMap;

// �ƹ�����
uniform vec3 lightPosition[MAX_LIGHT];	// λ��
uniform vec3 lightColor[MAX_LIGHT];		// ��ɫ
uniform vec3 attenuation[MAX_LIGHT];	// �ƹ�˥����ÿ��vec3����iλ�ö�Ӧ˥��i����

uniform float shininess = 128.0f;
uniform float reflectivity = 1.0f;
uniform vec3 skyColor;

out vec4 frag_out;

void main()
{
	vec3 n_ToCameraVector = normalize(toCameraVector);
	vec3 n_Normal = normalize(Normal);
	vec3 totalDiffuse = vec3(0.0f);
	vec3 totalSpecular = vec3(0.0f);
	vec3 toLightVector; // ��ƬԪ��������ָ���Դ��������
	vec3 n_ToLightVector;
	vec4 texture_color = texture(diffuseMap, TexCoord);

	if(texture_color.a < 0.5f) {
		discard;
	}

	// Ambient
	float ambient = 0.2f;

	for(int i=0; i < MAX_LIGHT; ++i) {
		// ��ƬԪ��������ָ���Դ��������
		toLightVector = lightPosition[i] - worldPosition;

		// Attenuation
		// ���ص㵽��Դ�ľ���
		float distance = length(toLightVector);
		// ����˥��ϵ��
		float attFactor = attenuation[i].x + (attenuation[i].y * distance)
			+ (attenuation[i].z * distance * distance);
		// ȡ˥�����������������Ϊ����˷�
		float oneDivideAttFactor = 1.0f / attFactor;

		// Diffuse
		n_ToLightVector = normalize(toLightVector);
		float diff = max(dot(n_Normal, n_ToLightVector), 0.0f);
		totalDiffuse += lightColor[i] * diff * oneDivideAttFactor;

		// Specular
		vec3 reflectDir = reflect(-n_ToLightVector, n_Normal);
		vec3 n_HalfWay = normalize(n_ToLightVector + n_ToCameraVector);
		float spec = pow(max(dot(n_Normal, n_HalfWay), 0.0f), shininess);
		totalSpecular += spec * lightColor[i] * reflectivity * oneDivideAttFactor;
	}

	if(useSpecularMap > 0.5f) {
		vec4 mapInfo = texture(specularMap, TexCoord);
		totalSpecular *= mapInfo.r + 0.3f;
	}

	frag_out = (vec4(totalDiffuse, 1.0f) + ambient) * texture_color  + vec4(totalSpecular, 1.0f);
	frag_out = mix(vec4(skyColor, 1.0f), frag_out, visibility);
}
