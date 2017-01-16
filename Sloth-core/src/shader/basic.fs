#version 450 core

#define MAX_LIGHT 4
uniform sampler2D tex0;
uniform vec3 lightPosition[MAX_LIGHT];
uniform vec3 lightColor[MAX_LIGHT];

out vec4 frag_out;

in DATA {
	vec3 pos;
	vec2 texCoord;
	vec3 normal;
} fs_in;

in vec3 worldPosition;

void main()
{
	vec3 toLightVector[4];
	vec3 n_Normal = normalize(fs_in.normal);
	vec3 totalDiffuse = vec3(0.0f);
	vec3 totalSpecular = vec3(0.0f);

	for(int i=0; i < MAX_LIGHT; ++i){
		toLightVector[i] = normalize(lightPosition[i] - worldPosition);
		float diff = max(dot(n_Normal, toLightVector[i]), 0.0f);
		totalDiffuse += lightColor[i] * diff;
	}
	frag_out = vec4(totalDiffuse, 1.0f) * texture(tex0, fs_in.texCoord);
}
