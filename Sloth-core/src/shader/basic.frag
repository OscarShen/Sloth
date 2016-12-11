#version 450 core

uniform vec2 light_pos;

out vec4 color;

in DATA {
	vec3 pos;
	vec4 color;
} fs_in;

void main()
{
	float intensity = 20.0f / length(gl_FragCoord.xy - light_pos);
	color = fs_in.color * intensity;
	//color = fs_in.color;
}