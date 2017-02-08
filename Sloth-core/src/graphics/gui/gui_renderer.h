/************************************************************************
* @project 		:  sloth
* @class   		:  GuiRenderer
* @version 		:  v1.0.0
* @description	:  GUI 渲染器
* @author		:  Oscar Shen
* @creat 		:  2017年2月8日17:20:19
* @revise 		:
************************************************************************
* Copyright @ OscarShen 2017. All rights reserved.
************************************************************************/
#pragma once
#ifndef SLOTH_GUI_RENDERER_H_
#define SLOTH_GUI_RENDERER_H_

#include "../model/raw_model.hpp"
#include "../engine/loader.h"
#include "gui_texture.hpp"
#include "gui_shader.h"
#include "../../utils/maths.h"
namespace sloth { namespace graphics {

	class GuiRenderer
	{
	private:
		RawModel m_Quad;

	public:
		GuiRenderer(Loader &loader);
		// 渲染所有容器内的gui
		void render(std::vector<GuiTexture> &guis);
	};

} }



#endif // !SLOTH_GUI_RENDERER_H_
