#pragma once
#ifndef SLOTH_MACRO_H_
#define SLOTH_MACRO_H_

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

#define GLSL_MAX_LIGHTS 4
// 着色器路径
#define STATIC_VERTEX_FILE "src/shader/basic.vert"
#define STATIC_FRAGMENT_FILE "src/shader/basic.frag"
#define TERRAIN_VERTEX_FILE "src/shader/terrain.vert"
#define TERRAIN_FRAGMENT_FILE "src/shader/terrain.frag"

// 地形设置
#define TERRAIN_SIZE 800.0f	// 地形大小为 TERRAIN_SIZE * TERRAIN_SIZE
//#define TERRAIN_VERTEX_COUNT 128 // 地形三角形细分程度
#define TERRAIN_MAX_HEIGHT 40.0f // 地形最高高度
#define TERRAIN_MAX_PIXEL_COLOR 256*256*256 //

#define PERSPECTIVE_FOV 45.0f
#define PERSPECTIVE_ASPECT (static_cast<float>(SCREEN_WIDTH)/SCREEN_HEIGHT)
#define PERSPECTIVE_NEAR_PLANE 0.1f
#define PERSPECTIVE_FAR_PLANE 1000.0f

#define CAMERA_INIT_POS		glm::vec3(0.0f,5.0f,0.0f)
#define CAMERA_INIT_UP		glm::vec3(0.0f,1.0f,0.0f)
#define CAMERA_INIT_FRONT	glm::vec3(0.0f,0.0f,-1.0f)
#define CAMERA_INIT_RIGHT	glm::normalize(glm::cross(CAMERA_INIT_UP, CAMERA_INIT_POS + CAMERA_INIT_FRONT))
#define CAMERA_INIT_PITCH	0.0f
#define CAMERA_INIT_YAW		-90.0f
#define MOUSE_SENSITIVITY	2.0f
#define MOVE_SPEED			20.0f

#define FOG_COLOR_RED 0.5f
#define FOG_COLOR_BLUE 0.5f
#define FOG_COLOR_GREEN 0.5f

// 键盘和鼠标输入的按键个数
#define MAX_KEYS 1024
#define MAX_MOUSE_BOTTON 32

#define DEFUALT_CLEAR_COLOR_RED 0.5f
#define DEFUALT_CLEAR_COLOR_GREEN 0.5f
#define DEFUALT_CLEAR_COLOR_BLUE 0.5f


// 关于角色移动、跳跃的宏定义		/src/graphics/entities/player
#define PLAYER_RUN_SPEED 20.0f
#define PLAYER_TURN_SPEED 10.0f
#define PLAYER_GRAVITY -50.0f
#define PLAYER_JUMP_POWER 30.0f
#define PLAYER_TERRAIN_HEIGHT 0.0f

#endif // !SLOTH_MACRO_H_
