#version 450 core

// 最大灯光数
#define MAX_LIGHT 4
// One terrain texture to tile n times in a edge
#define TERRAIN_TILE_NUMBLE 40.0f

// 灯光属性
uniform vec3 lightPosition[MAX_LIGHT];	// 位置
uniform vec3 lightColor[MAX_LIGHT];		// 颜色
uniform vec3 attenuation[MAX_LIGHT];	// 灯光衰减，每个vec3向量i位置对应衰减i次项

uniform float shininess = 128.0f;
uniform float reflectivity = 1.0f;
uniform vec3 skyColor;

uniform sampler2D backgroundTexture;
uniform sampler2D rTexture;
uniform sampler2D gTexture;
uniform sampler2D bTexture;
uniform sampler2D blendMap;

// 阴影
uniform sampler2D shadowMap;

out vec4 frag_out;

in DATA {
	vec3 pos;
	vec2 texCoord;
	vec3 normal;
} fs_in;

in vec3 worldPosition;
in vec3 toCameraVector;
in float visibility;
in vec4 LightSpacePos;

bool inShadow(vec4 lightSpacePos)
{
	// 透视除法
	vec3 projCoords = lightSpacePos.xyz / lightSpacePos.w;
	// 变换到 [0,1]
	projCoords = projCoords * 0.5f + 0.5f;
	// 最近深度
	float closestDepth = texture(shadowMap, projCoords.xy).r;
	// 光源视角下的深度
	float currentDepth = projCoords.z;
	// 检查是否在阴影中
	if(currentDepth > closestDepth)
		return true;
	return false;
}

void main()
{
	vec4 blendMapColor = texture(blendMap, fs_in.texCoord);
	float backTextureAmount = 1.0f - (blendMapColor.r + blendMapColor.g + blendMapColor.b);
	vec2 tiledCoords = fs_in.texCoord * TERRAIN_TILE_NUMBLE;
	vec4 backgroundTextureColor = texture(backgroundTexture, tiledCoords) * backTextureAmount;
	vec4 rTextureColor = texture(rTexture, tiledCoords) * blendMapColor.r;
	vec4 gTextureColor = texture(gTexture, tiledCoords) * blendMapColor.g;
	vec4 bTextureColor = texture(bTexture, tiledCoords) * blendMapColor.b;
	vec4 totalColor = backgroundTextureColor + rTextureColor + gTextureColor + bTextureColor;

	vec3 n_ToCameraVector = normalize(toCameraVector);
	vec3 n_Normal = normalize(fs_in.normal);
	vec3 totalDiffuse = vec3(0.0f);
	vec3 totalSpecular = vec3(0.0f);
	vec3 toLightVector; // 从片元世界坐标指向光源世界坐标
	vec3 n_ToLightVector;

	// Ambient
	float ambient = 0.2f;

	// 阴影指数
	float shadowIndex = 1.0f;
	for(int i=0; i < MAX_LIGHT; ++i){
		// 从片元世界坐标指向光源世界坐标
		toLightVector = lightPosition[i] - worldPosition;
	
		// Attenuation
		// 像素点到光源的距离
		float distance = length(toLightVector);
		// 计算衰减系数
		float attFactor = attenuation[i].x + (attenuation[i].y * distance)
			+ (attenuation[i].z * distance * distance);
		// 取衰减倒数，化浮点除法为浮点乘法
		float oneDivideAttFactor = 1.0f / attFactor;
	
		// Diffuse
		n_ToLightVector = normalize(lightPosition[i] - worldPosition);
		float diff = max(dot(n_Normal, n_ToLightVector), 0.0f);
		totalDiffuse += lightColor[i] * diff * oneDivideAttFactor;
	
		// Specular
		vec3 reflectDir = reflect(-n_ToLightVector, n_Normal);
		vec3 n_HalfWay = normalize(n_ToLightVector + n_ToCameraVector);
		float spec = pow(max(dot(n_Normal, n_HalfWay), 0.0f), shininess);
		totalSpecular += spec * lightColor[i] * reflectivity * oneDivideAttFactor;

		// 阴影
		if(inShadow(LightSpacePos))
			shadowIndex = 0.6f;
	}
	frag_out = (vec4(totalDiffuse, 1.0f) * shadowIndex  + ambient) * totalColor + vec4(totalSpecular, 1.0f);
	frag_out = mix(vec4(skyColor, 1.0f), frag_out, visibility);
}