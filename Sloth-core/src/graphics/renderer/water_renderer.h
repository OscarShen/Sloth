/************************************************************************ 
 * @project 	:  sloth
 * @class   	:  WaterRenderer
 * @version 	:  v1.0.0
 * @description :  water 的渲染操作类
 * @author		:  Oscar Shen
 * @creat 		:  2017年2月13日21:54:09
 * @revise 		:  
************************************************************************ 
 * Copyright @ OscarShen 2017. All rights reserved. 
************************************************************************/  
#pragma once
#ifndef SLOTH_WATER_RENDERER_H_
#define SLOTH_WATER_RENDERER_H_

#include "../model/raw_model.hpp"
#include "../engine/loader.h"
#include "../shader/water_shader.h"
#include "../water/water_tile.hpp"
#include "../water/water_frame_buffer.h"
#include "../../utils/maths.h"

// dudv map 路径
#define DUDV_MAP_PATH "res/textures/dudvMap.png"
// 水波荡漾参数
#define WATER_WAVE_SPEED 0.03f


namespace sloth { namespace graphics {

	class WaterRenderer
	{
	private:
		RawModel m_Quad;
		// dudv map texture 的句柄
		unsigned int m_DudvMap;

		WaterFrameBuffer &m_Wfbo;

		float m_MoveFactor = 0.0f;

	public:
		WaterRenderer(Loader &loader, const glm::mat4 &projection , WaterFrameBuffer &waterfbo);

		/***********************************************************************
		* @description	: 构造天空盒renderer
		* @author		: Oscar Shen
		* @creat		: 2017年2月13日21:54:54
		***********************************************************************/
		void render(std::vector<WaterTile> &water, RawCamera &camera);

	private:
		/***********************************************************************
		* @description	: 设定水面VAO
		* @author		: Oscar Shen
		* @creat		: 2017年2月13日21:55:36
		***********************************************************************/
		void setVAO(Loader &loader);

		/***********************************************************************
		* @description	: 准备渲染工作
		* @author		: Oscar Shen
		* @creat		: 2017年2月20日12:05:21
		***********************************************************************/
		void prepareRender(const RawCamera &camera);

		/***********************************************************************
		* @description	: 回复默认状态
		* @author		: Oscar Shen
		* @creat		: 2017年2月20日12:05:38
		***********************************************************************/
		void unbind();
	};

} }

#endif // !SLOTH_WATER_RENDERER_H_
