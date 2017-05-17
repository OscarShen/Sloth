/************************************************************************ 
 * @project 	:  $rootnamespace$
 * @class   	:  $safeitemrootname$
 * @version 	:  v1.0.0
 * @description :  
 * @author		:  $username$
 * @creat 		:  $time$
 * @revise 		:  $time$
************************************************************************ 
 * Copyright @ OscarShen 2017. All rights reserved. 
************************************************************************/  
#pragma once
#ifndef SLOTH_HEADER_H_
#define SLOTH_HEADER_H_

#include <vector>
#include <memory>
#include <map>
#include <iostream>

#define WATER

#ifdef WATER

#define SCREEN_WIDTH 1600
#define SCREEN_HEIGHT 900

#define DEFAULT_TEXTURE_WRAP_S GL_REPEAT
#define DEFAULT_TEXTURE_WRAP_T GL_REPEAT
#define DEFAULT_TEXTURE_MIN_FILTER GL_NEAREST_MIPMAP_LINEAR
#define DEFAULT_TEXTURE_MAG_FILTER GL_LINEAR

#define GLSL_MAX_LIGHTS 4
// 着色器路径 path of shaders
// 静态着色器 static shader
#define STATIC_VERTEX_FILE "src/shader/basic.vert"
#define STATIC_FRAGMENT_FILE "src/shader/basic.frag"
// 地形着色器 terrain shader
#define TERRAIN_VERTEX_FILE "src/shader/terrain.vert"
#define TERRAIN_FRAGMENT_FILE "src/shader/terrain.frag"
// GUI着色器  GUI shader
#define GUI_VERTEX_FILE "src/shader/gui.vert"
#define GUI_FRAGMENT_FILE "src/shader/gui.frag"
// 天空盒着色器 skybox shader
#define SKYBOX_VERTEX_FILE "src/shader/skybox.vert"
#define SKYBOX_FRAGMENT_FILE "src/shader/skybox.frag"
// 水面着色器 water shader
#define WATER_VERTEX_FILE "src/shader/water.vert"
#define WATER_FRAGMENT_FILE "src/shader/water.frag"

// 地形设置
#define TERRAIN_SIZE 400.0f	// 地形大小为 TERRAIN_SIZE * TERRAIN_SIZE
//#define TERRAIN_VERTEX_COUNT 128 // 地形三角形细分程度
#define TERRAIN_MAX_HEIGHT 40 // 地形最高高度
#define TERRAIN_MAX_PIXEL_COLOR 256*256*256 //

#define PERSPECTIVE_FOV 45.0f
#define PERSPECTIVE_ASPECT (static_cast<float>(SCREEN_WIDTH)/SCREEN_HEIGHT)
#define PERSPECTIVE_NEAR_PLANE 0.1f
#define PERSPECTIVE_FAR_PLANE 1000.0f

#define CAMERA_INIT_POS		glm::vec3(0.0f,5.0f,0.0f)
#define CAMERA_INIT_UP		glm::vec3(0.0f,1.0f,0.0f)
#define CAMERA_INIT_FRONT	glm::vec3(-1.0f,0.0f,-1.0f)
#define CAMERA_INIT_RIGHT	glm::normalize(glm::cross(CAMERA_INIT_UP, CAMERA_INIT_POS + CAMERA_INIT_FRONT))
#define CAMERA_INIT_PITCH	0.0f
#define CAMERA_INIT_YAW		-90.0f
#define MOUSE_SENSITIVITY	1.0f
#define MOVE_SPEED			30.0f

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
#define PLAYER_TURN_SPEED 60.0f
#define PLAYER_GRAVITY -50.0f
#define PLAYER_JUMP_POWER 30.0f

/************************************************************************
* @description	: 二分法查找地形X和Z坐标的迭代次数
* @author		: Oscar Shen
* @creat		: 2017年2月12日19:21:38
***********************************************************************/
#define MOUSE_PICKER_RECURSION_COUNT 200
/************************************************************************
* @description	: 鼠标选取发出光线的最大范围
* @author		: Oscar Shen
* @creat		: 2017年2月12日19:21:38
***********************************************************************/
#define MOUSE_PICKER_RAY_CASTING_RANGE 600.0f

// 位置：src/water/water_tile
#define WATER_TILE_SIZE 200.0f
// 位置：src/water/water_frame_buffer
#define WATER_REFLECTION_WIDTH 1280	// 水面反射纹理宽度
#define WATER_REFLECTION_HEIGHT 720 // 水面反射纹理高度
#define WATER_REFRACTION_WIDTH 1280	// 水面折射纹理高度
#define WATER_REFRACTION_HEIGHT 720	// 水面折射纹理宽度

#endif // WATER

#endif // LAND
