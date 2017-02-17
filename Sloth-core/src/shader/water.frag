#version 450 core

in vec4 clipSpace;

uniform sampler2D reflectionTexture;
uniform sampler2D refractionTexture;

out vec4 out_Color;


void main(void) {

	vec2 ndc = (clipSpace.xy / clipSpace.w) / 2.0f + 0.5f;

	vec2 reflectionTexCoord = vec2(ndc.x, -ndc.y);
	vec2 refractionTexCoord = vec2(ndc.x, ndc.y);

	vec4 reflectionColor = texture(reflectionTexture, reflectionTexCoord);
	vec4 refractionColor = texture(refractionTexture, refractionTexCoord);

	out_Color = mix(reflectionColor, refractionColor, 0.5f);
	//out_Color = reflectionColor;
}