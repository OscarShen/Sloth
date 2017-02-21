#version 450 core

in vec4 clipSpace;
in vec2 texCoord;
in vec3 toCameraVector;
in vec3 out_WorldPosition;

uniform sampler2D reflectionTexture;
uniform sampler2D refractionTexture;
uniform sampler2D dudvMap;
uniform sampler2D normalMap;
uniform sampler2D depthMap;
uniform vec3 lightColor;
uniform vec3 lightPosition;

// 水波荡漾
uniform float moveFactor;

out vec4 out_Color;

const float waveStrength = 0.02f;
const float shineDamper = 20.0f;
const float reflectivity = 0.3f;

void main(void) {

	// 投影纹理映射获得的ndc坐标，进行了透视除法
	vec2 ndc = (clipSpace.xy / clipSpace.w) / 2.0f + 0.5f;

	// 纹理坐标
	vec2 reflectionTexCoord = vec2(ndc.x, -ndc.y);
	vec2 refractionTexCoord = vec2(ndc.x, ndc.y);

	// 计算水深（从相机光线发出，从水面到水底的距离）
	// TODO! 加入uniform
	float near = 0.01f;
	float far = 1000.0f;
	float depth = texture(depthMap, refractionTexCoord).x;
	float floorDistance = 2.0f * near * far / (far + near - (2.0f * depth -1.0f) * (far - near));

	depth = gl_FragCoord.z;
	float waterDistance = 2.0f * near * far / (far + near - (2.0f * depth -1.0f) * (far - near));

	float waterDepth = floorDistance - waterDistance;


	// 水流效果
	//vec2 distortion1 = (texture(dudvMap, vec2(texCoord.x + moveFactor, texCoord.y)).rg * 2.0f - 1.0f) * waveStrength;
	//vec2 distortion2 = (texture(dudvMap, vec2(-texCoord.x + moveFactor, texCoord.y + moveFactor)).rg * 2.0f - 1.0f) * waveStrength;
	//vec2 totalDistortion = distortion1 + distortion2;
	vec2 distortedTexCoord = texture(dudvMap, vec2(texCoord.x + moveFactor, texCoord.y)).rg * 0.1f;
	distortedTexCoord = texCoord + vec2(distortedTexCoord.x, distortedTexCoord.y + moveFactor);
	vec2 totalDistortion = (texture(dudvMap, distortedTexCoord).rg * 2.0f - 1.0f) * waveStrength * clamp(waterDepth / 10.0f, 0.0f, 1.0f);

	reflectionTexCoord += totalDistortion;
	reflectionTexCoord.x = clamp(reflectionTexCoord.x, 0.001f, 0.999f);
	reflectionTexCoord.y = clamp(reflectionTexCoord.y, -0.999f, -0.001f);

	refractionTexCoord += totalDistortion;
	refractionTexCoord = clamp(refractionTexCoord, 0.001f, 0.999f);

	vec4 reflectionColor = texture(reflectionTexture, reflectionTexCoord);
	vec4 refractionColor = texture(refractionTexture, refractionTexCoord);

	// 法向贴图
	vec4 normalMapColor = texture(normalMap, distortedTexCoord);
	vec3 normal = vec3(normalMapColor.r * 2.0f - 1.0f, normalMapColor.b, normalMapColor.g * 2.0f - 1.0f);
	normal = normalize(normal);

	vec3 n_ToCamera =  normalize(toCameraVector);
	float refractiveFactor = clamp(dot(n_ToCamera, normal), 0.0f, 1.0f);
	// 折射占据上风
	refractiveFactor = pow(refractiveFactor, 0.5f);

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
	//out_Color.a = clamp(waterDepth / 2.0f, 0.0f, 1.0f);
}