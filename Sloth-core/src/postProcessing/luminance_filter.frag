#version 450 core

in vec2 textureCoords;

out vec4 out_Color;

uniform sampler2D colorTexture;
uniform float thresHold;

void main(void) {
	vec4 color = texture(colorTexture, textureCoords);
	float luminance = (color.r * 0.2126) + (color.g * 0.7152) + (color.b * 0.0722); // 亮度计算公式
	//out_Color = vec4(0.0f);
	//if(luminance > thresHold){
	//	out_Color = color;
	//}
	out_Color = color * luminance * luminance * luminance;
}