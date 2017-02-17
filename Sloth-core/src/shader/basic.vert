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
uniform float useFakeLignting;

uniform float numberOfRows; // atlases ������
uniform vec2 offset; // ��¼��ǰ��Ҫ��������atalases�еĿ�ʼ��
uniform vec4 clipPlane;		// �ü�ƽ��

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
	vec4 worldPosition4 = model * vec4(position, 1.0f);
	worldPosition = worldPosition4.xyz;
	
	gl_ClipDistance[0] = dot(worldPosition4, clipPlane);

	vec4 positionInViewSpace = view * worldPosition4;
	gl_Position = projection * positionInViewSpace;
	vs_out.pos = position;
	vs_out.texCoord = (texCoord / numberOfRows) + offset;

	vec3 actualNormal = normal;
	if(useFakeLignting > 0.5f) {
		actualNormal = vec3(0.0f, 1.0f, 0.0f);
	}

	vs_out.normal = mat3(transpose(inverse(model))) * actualNormal;
	toCameraVector = (inverse(view) * vec4(0.0f,0.0f,0.0f,1.0f)).xyz - worldPosition;

	float distance = length(positionInViewSpace.xyz);
	visibility = exp(-pow((distance * FOG_DENSITY), FOG_GRADIENT));
	visibility = clamp(visibility, 0.0f, 1.0f);
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
uniform float useFakeLignting;

uniform float numberOfRows; // atlases ������
uniform vec2 offset; // ��¼��ǰ��Ҫ��������atalases�еĿ�ʼ��


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
	vs_out.texCoord = (texCoord / numberOfRows) + offset;

	vec3 actualNormal = normal;
	if(useFakeLignting > 0.5f) {
		actualNormal = vec3(0.0f, 1.0f, 0.0f);
	}

	vs_out.normal = mat3(transpose(inverse(model))) * actualNormal;
	toCameraVector = (inverse(view) * vec4(0.0f,0.0f,0.0f,1.0f)).xyz - worldPosition;

	float distance = length(positionInViewSpace.xyz);
	visibility = exp(-pow((distance * FOG_DENSITY), FOG_GRADIENT));
	visibility = clamp(visibility, 0.0f, 1.0f);
}
#endif