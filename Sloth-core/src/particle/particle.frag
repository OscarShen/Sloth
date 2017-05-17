#version 450 core

in vec2 texCoordNow;
in vec2 texCoordNext;
in float blend;

out vec4 out_color;

uniform sampler2D particleTexture;

void main(void){
	vec4 colorNow = texture(particleTexture, texCoordNow);
	vec4 colorNext = texture(particleTexture, texCoordNext);

	out_color = mix(colorNow, colorNext, blend);
}