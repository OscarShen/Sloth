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

namespace sloth { namespace graphics {

	class WaterRenderer
	{
	private:
		RawModel m_Quad;
		WaterFrameBuffer &m_Wfbo;

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
	};

} }



#endif // !SLOTH_WATER_RENDERER_H_
