#version 450 core

#define WATER
#ifdef WATER

// In fog it has : visibility = exp(-(distance * density)^gradient)
#define FOG_DENSITY 0.0035f
#define FOG_GRADIENT 5.0f

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texCoord;
layout (location = 2) in vec3 normal;

uniform mat4 projection = mat4(1.0f);
uniform mat4 view = mat4(1.0f);
uniform mat4 model = mat4(1.0f);
uniform vec4 clipPlane;		// 裁剪平面

// 阴影光照空间
uniform mat4 lightSpace;

out DATA {
	vec3 pos;
	vec2 texCoord;
	vec3 normal;
} vs_out;

out vec3 worldPosition;
out vec3 toCameraVector;
out float visibility;

// 光照空间的片元位置
out vec4 LightSpacePos;

void main()
{
	vec4 worldPosition4 = model * vec4(position, 1.0f);
	worldPosition = worldPosition4.xyz;
	
	gl_ClipDistance[0] = dot(worldPosition4, clipPlane);

	vec4 positionInViewSpace = view * worldPosition4;
	gl_Position = projection * positionInViewSpace;
	vs_out.pos = position;
	vs_out.texCoord = texCoord;
	vs_out.normal = mat3(transpose(inverse(model))) * normal;
	toCameraVector = (inverse(view) * vec4(0.0f,0.0f,0.0f,1.0f)).xyz - worldPosition;

	float distance = length(positionInViewSpace.xyz);
	visibility = exp(-pow((distance * FOG_DENSITY), FOG_GRADIENT));
	visibility = clamp(visibility, 0.0f, 1.0f);

	// 阴影
	LightSpacePos = lightSpace * worldPosition4;
}

#endif

#ifdef LAND
// In fog it has : visibility = exp(-(distance * density)^gradient)
#define FOG_DENSITY 0.0035f
#define FOG_GRADIENT 5.0f

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texCoord;
layout (location = 2) in vec3 normal;

uniform mat4 projection = mat4(1.0f);
uniform mat4 view = mat4(1.0f);
uniform mat4 model = mat4(1.0f);

out DATA {
	vec3 pos;
	vec2 texCoord;
	vec3 normal;
} vs_out;

out vec3 worldPosition;
out vec3 toCameraVector;
out float visibility;

void main()
{
	worldPosition = vec3(model * vec4(position, 1.0f));
	vec4 positionInViewSpace = view * vec4(worldPosition, 1.0f);
	gl_Position = projection * positionInViewSpace;
	vs_out.pos = position;
	vs_out.texCoord = texCoord;
	vs_out.normal = mat3(transpose(inverse(model))) * normal;
	toCameraVector = (inverse(view) * vec4(0.0f,0.0f,0.0f,1.0f)).xyz - worldPosition;

	float distance = length(positionInViewSpace.xyz);
	visibility = exp(-pow((distance * FOG_DENSITY), FOG_GRADIENT));
	visibility = clamp(visibility, 0.0f, 1.0f);
}
#endif