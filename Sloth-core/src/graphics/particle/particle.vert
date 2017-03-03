#version 450 core

in vec2 position;

uniform mat4 projection;
uniform mat4 modelView;

void main(void){

	gl_Position = projection * modelView * vec4(position, 0.0, 1.0);

}