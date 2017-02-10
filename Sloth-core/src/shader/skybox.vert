#version 450 core

layout(location = 0) in vec3 position;
out vec3 textureCoords;

uniform mat4 projection;
uniform mat4 view;

void main(void){
    // 使天空盒的深度最大
	vec4 pos = projection * view * vec4(position, 1.0);
	gl_Position = pos.xyww;
	
	//gl_Position = projection * view * vec4(position, 1.0);
	textureCoords = position;
}