#version 450 core

// 最大灯光数
#define MAX_LIGHT 4

// In fog it has : visibility = exp(-(distance * density)^gradient)
#define FOG_DENSITY 0.0035f
#define FOG_GRADIENT 5.0f

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texCoord;
layout (location = 2) in vec3 normal;
layout (location = 3) in vec3 tangent;

uniform mat4 projection = mat4(1.0f);
uniform mat4 view = mat4(1.0f);
uniform mat4 model = mat4(1.0f);

uniform float numberOfRows; // atlases 的行数
uniform vec2 offset; // 记录当前需要的纹理在atalases中的开始点
uniform vec4 clipPlane;		// 裁剪平面
uniform vec3 lightPosition[MAX_LIGHT];	// 灯光位置

out vec2 TexCoord;
out vec3 lightPosition_Tangent[MAX_LIGHT];
out vec3 worldPosition_Tangent;
out vec3 toCameraVector_Tangent;
out float visibility;

void main()
{
	vec4 worldPosition4 = model * vec4(position, 1.0f);
	
	gl_ClipDistance[0] = dot(worldPosition4, clipPlane);

	vec4 positionInViewSpace = view * worldPosition4;
	gl_Position = projection * positionInViewSpace;

	TexCoord = (texCoord / numberOfRows) + offset;

	mat3 normalMatrix = mat3(transpose(inverse(model)));
	vec3 T = normalize(normalMatrix * tangent);
	vec3 N = normalize(normalMatrix * normal);
	vec3 B = normalize(cross(N, T));

	mat3 TBN = transpose(mat3(T, B, N));

	toCameraVector_Tangent = TBN * ((inverse(view) * vec4(0.0f,0.0f,0.0f,1.0f)).xyz - worldPosition4.xyz);
	worldPosition_Tangent = TBN * worldPosition4.xyz;
	for(int i=0;i<MAX_LIGHT;++i) {
		lightPosition_Tangent[i] = TBN * lightPosition[i];
	}

	float distance = length(positionInViewSpace.xyz);
	visibility = exp(-pow((distance * FOG_DENSITY), FOG_GRADIENT));
	visibility = clamp(visibility, 0.0f, 1.0f);
}
