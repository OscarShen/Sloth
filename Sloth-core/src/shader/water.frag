#version 450 core

in vec4 clipSpace;
in vec2 texCoord;
in vec3 toCameraVector;
in vec3 out_WorldPosition;

uniform sampler2D reflectionTexture;
uniform sampler2D refractionTexture;
uniform sampler2D dudvMap;
uniform sampler2D normalMap;
uniform vec3 lightColor;
uniform vec3 lightPosition;

// 水波荡漾
uniform float moveFactor;

out vec4 out_Color;

const float waveStrength = 0.02f;
const float shineDamper = 20.0f;
const float reflectivity = 0.6f;

void main(void) {

	// 投影纹理映射获得的ndc坐标，进行了透视除法
	vec2 ndc = (clipSpace.xy / clipSpace.w) / 2.0f + 0.5f;

	// 纹理坐标
	vec2 reflectionTexCoord = vec2(ndc.x, -ndc.y);
	vec2 refractionTexCoord = vec2(ndc.x, ndc.y);

	// 水流效果
	//vec2 distortion1 = (texture(dudvMap, vec2(texCoord.x + moveFactor, texCoord.y)).rg * 2.0f - 1.0f) * waveStrength;
	//vec2 distortion2 = (texture(dudvMap, vec2(-texCoord.x + moveFactor, texCoord.y + moveFactor)).rg * 2.0f - 1.0f) * waveStrength;
	//vec2 totalDistortion = distortion1 + distortion2;
	vec2 distortedTexCoord = texture(dudvMap, vec2(texCoord.x + moveFactor, texCoord.y)).rg * 0.1f;
	distortedTexCoord = texCoord + vec2(distortedTexCoord.x, distortedTexCoord.y + moveFactor);
	vec2 totalDistortion = (texture(dudvMap, distortedTexCoord).rg * 2.0f - 1.0f) * waveStrength;

	reflectionTexCoord += totalDistortion;
	reflectionTexCoord.x = clamp(reflectionTexCoord.x, 0.001f, 0.999f);
	reflectionTexCoord.y = clamp(reflectionTexCoord.y, -0.999f, -0.001f);

	refractionTexCoord += totalDistortion;
	refractionTexCoord = clamp(refractionTexCoord, 0.001f, 0.999f);


	vec4 reflectionColor = texture(reflectionTexture, reflectionTexCoord);
	vec4 refractionColor = texture(refractionTexture, refractionTexCoord);

	vec3 n_ToCamera =  normalize(toCameraVector);
	float refractiveFactor = dot(n_ToCamera, vec3(0.0f, 1.0f, 0.0f));
	// 折射占据上风
	refractiveFactor = pow(refractiveFactor, 0.5f);

	// 法向贴图
	vec4 normalMapColor = texture(normalMap, distortedTexCoord);
	vec3 normal = vec3(normalMapColor.r * 2.0f - 1.0f, normalMapColor.b, normalMapColor.g * 2.0f - 1.0f);
	normal = normalize(normal);

	// 计算水面高亮
	vec3 n_FromLightVector = normalize(out_WorldPosition - lightPosition);
	vec3 reflectedLight = reflect(n_FromLightVector, normal);
	float spec = max(dot(reflectedLight, n_ToCamera), 0.0f);
	spec = pow(spec, shineDamper);
	vec3 specular = lightColor * spec * reflectivity;


	out_Color = mix(reflectionColor, refractionColor, refractiveFactor);
	// 增加一点蓝色
	out_Color = mix(out_Color, vec4(0.0f, 0.3f, 0.5f, 1.0f), 0.1f);
	out_Color += vec4(specular, 0.0f);
}