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
// ��ɫ��·�� path of shaders
// ��̬��ɫ�� static shader
#define STATIC_VERTEX_FILE "src/shader/basic.vert"
#define STATIC_FRAGMENT_FILE "src/shader/basic.frag"
// ������ɫ�� terrain shader
#define TERRAIN_VERTEX_FILE "src/shader/terrain.vert"
#define TERRAIN_FRAGMENT_FILE "src/shader/terrain.frag"
// GUI��ɫ��  GUI shader
#define GUI_VERTEX_FILE "src/shader/gui.vert"
#define GUI_FRAGMENT_FILE "src/shader/gui.frag"
// ��պ���ɫ�� skybox shader
#define SKYBOX_VERTEX_FILE "src/shader/skybox.vert"
#define SKYBOX_FRAGMENT_FILE "src/shader/skybox.frag"
// ˮ����ɫ�� water shader
#define WATER_VERTEX_FILE "src/shader/water.vert"
#define WATER_FRAGMENT_FILE "src/shader/water.frag"

// ��������
#define TERRAIN_SIZE 400.0f	// ���δ�СΪ TERRAIN_SIZE * TERRAIN_SIZE
//#define TERRAIN_VERTEX_COUNT 128 // ����������ϸ�̶ֳ�
#define TERRAIN_MAX_HEIGHT 40 // ������߸߶�
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

// ���̺��������İ�������
#define MAX_KEYS 1024
#define MAX_MOUSE_BOTTON 32

#define DEFUALT_CLEAR_COLOR_RED 0.5f
#define DEFUALT_CLEAR_COLOR_GREEN 0.5f
#define DEFUALT_CLEAR_COLOR_BLUE 0.5f


// ���ڽ�ɫ�ƶ�����Ծ�ĺ궨��		/src/graphics/entities/player
#define PLAYER_RUN_SPEED 20.0f
#define PLAYER_TURN_SPEED 60.0f
#define PLAYER_GRAVITY -50.0f
#define PLAYER_JUMP_POWER 30.0f

/************************************************************************
* @description	: ���ַ����ҵ���X��Z����ĵ�������
* @author		: Oscar Shen
* @creat		: 2017��2��12��19:21:38
***********************************************************************/
#define MOUSE_PICKER_RECURSION_COUNT 200
/************************************************************************
* @description	: ���ѡȡ�������ߵ����Χ
* @author		: Oscar Shen
* @creat		: 2017��2��12��19:21:38
***********************************************************************/
#define MOUSE_PICKER_RAY_CASTING_RANGE 600.0f

// λ�ã�src/water/water_tile
#define WATER_TILE_SIZE 200.0f
// λ�ã�src/water/water_frame_buffer
#define WATER_REFLECTION_WIDTH 1280	// ˮ�淴��������
#define WATER_REFLECTION_HEIGHT 720 // ˮ�淴������߶�
#define WATER_REFRACTION_WIDTH 1280	// ˮ����������߶�
#define WATER_REFRACTION_HEIGHT 720	// ˮ������������

#endif // WATER

#endif // LAND
