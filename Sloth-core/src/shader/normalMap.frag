#version 450 core

// 最大灯光数
#define MAX_LIGHT 4

in vec2 TexCoord;
in float visibility;
in vec3 lightPosition_Tangent[MAX_LIGHT];
in vec3 worldPosition_Tangent;
in vec3 toCameraVector_Tangent;
uniform sampler2D diffuseMap;
uniform sampler2D normalMap;
uniform sampler2D specularMap;
uniform float useSpecularMap;

// 灯光属性
//uniform vec3 lightPosition[MAX_LIGHT];	// 位置
uniform vec3 lightColor[MAX_LIGHT];		// 颜色
uniform vec3 attenuation[MAX_LIGHT];	// 灯光衰减，每个vec3向量i位置对应衰减i次项

uniform float shininess = 128.0f;
uniform float reflectivity = 1.0f;
uniform vec3 skyColor;

out vec4 frag_out;

void main()
{
	vec3 n_ToCameraVector = normalize(toCameraVector_Tangent);
	vec3 normal = texture(normalMap, TexCoord).rgb;
	vec3 n_Normal = normalize(normal * 2.0f - 1.0f);
	vec3 totalDiffuse = vec3(0.0f);
	vec3 totalSpecular = vec3(0.0f);
	vec3 toLightVector; // 从片元世界坐标指向光源世界坐标
	vec3 n_ToLightVector;
	vec4 texture_color = texture(diffuseMap, TexCoord);

	if(texture_color.a < 0.5f) {
		discard;
	}

	// Ambient
	float ambient = 0.2f;

	for(int i=0; i < MAX_LIGHT; ++i) {
		// 从片元世界坐标指向光源世界坐标
		toLightVector = lightPosition_Tangent[i] - worldPosition_Tangent;

		// Attenuation
		// 像素点到光源的距离
		float distance = length(toLightVector);
		// 计算衰减系数
		float attFactor = attenuation[i].x + (attenuation[i].y * distance)
			+ (attenuation[i].z * distance * distance);
		// 取衰减倒数，化浮点除法为浮点乘法
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

	// 高亮贴图
	if(useSpecularMap > 0.5f) {
		vec4 mapInfo = texture(specularMap, TexCoord);
		totalSpecular *= mapInfo.r + 0.3f;
	}

	frag_out = (vec4(totalDiffuse, 1.0f) + ambient) * texture_color  + vec4(totalSpecular, 1.0f);
	frag_out = mix(vec4(skyColor, 1.0f), frag_out, visibility);
}
