#version 450 core

#define MAX_LIGHT 4
uniform sampler2D tex0;

uniform vec3 lightPosition[MAX_LIGHT];
uniform vec3 lightColor[MAX_LIGHT];
uniform float shininess = 128.0f;
uniform float reflectivity = 1.0f;
uniform vec3 skyColor;

out vec4 frag_out;

in DATA {
	vec3 pos;
	vec2 texCoord;
	vec3 normal;
} fs_in;

in vec3 worldPosition;
in vec3 toCameraVector;
in float visibility;

void main()
{
	vec3 n_ToCameraVector = normalize(toCameraVector);
	vec3 n_Normal = normalize(fs_in.normal);
	vec3 totalDiffuse = vec3(0.0f);
	vec3 totalSpecular = vec3(0.0f);
	vec3 n_ToLightVector;
	vec4 texture_color = texture(tex0, fs_in.texCoord);

	if(texture_color.a < 0.5f) {
		discard;
	}

	// Ambient
	float ambient = 0.2f;
	for(int i=0; i < MAX_LIGHT; ++i){
		// Diffuse
		n_ToLightVector = normalize(lightPosition[i] - worldPosition);
		float diff = max(dot(n_Normal, n_ToLightVector), 0.0f);
		totalDiffuse += lightColor[i] * diff;

		// Specular
		vec3 reflectDir = reflect(-n_ToLightVector, n_Normal);
		vec3 n_HalfWay = normalize(n_ToLightVector + n_ToCameraVector);
		float spec = pow(max(dot(n_Normal, n_HalfWay), 0.0f), shininess);
		totalSpecular += spec * lightColor[i] * reflectivity * 0.3;
	}
	frag_out = (vec4(totalDiffuse, 1.0f) + ambient) * texture_color  + vec4(totalSpecular, 1.0f);
	frag_out = mix(vec4(skyColor, 1.0f), frag_out, visibility);
}
