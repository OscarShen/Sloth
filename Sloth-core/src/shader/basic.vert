#version 450 core

// In fog it has : visibility = exp(-(distance * density)^gradient)
#define FOG_DENSITY 0.0035f
#define FOG_GRADIENT 5.0f

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texCoord;
layout (location = 2) in vec3 normal;

uniform mat4 projection = mat4(1.0f);
uniform mat4 view = mat4(1.0f);
uniform mat4 model = mat4(1.0f);
uniform float useFakeLignting;

uniform float numberOfRows; // atlases 的行数
uniform vec2 offset; // 记录当前需要的纹理在atalases中的开始点
uniform vec4 clipPlane;		// 裁剪平面

out vec2 TexCoord;
out vec3 Normal;
out vec3 worldPosition;
out vec3 toCameraVector;
out float visibility;

void main()
{
	vec4 worldPosition4 = model * vec4(position, 1.0f);
	worldPosition = worldPosition4.xyz;
	
	gl_ClipDistance[0] = dot(worldPosition4, clipPlane);

	vec4 positionInViewSpace = view * worldPosition4;
	gl_Position = projection * positionInViewSpace;
	TexCoord = (texCoord / numberOfRows) + offset;

	vec3 actualNormal = normal;
	if(useFakeLignting > 0.5f) {
		actualNormal = vec3(0.0f, 1.0f, 0.0f);
	}

	Normal = mat3(transpose(inverse(model))) * actualNormal;
	toCameraVector = (inverse(view) * vec4(0.0f,0.0f,0.0f,1.0f)).xyz - worldPosition;

	float distance = length(positionInViewSpace.xyz);
	visibility = exp(-pow((distance * FOG_DENSITY), FOG_GRADIENT));
	visibility = clamp(visibility, 0.0f, 1.0f);
}
