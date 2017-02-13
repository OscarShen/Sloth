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
#ifndef SLOTH_WATER_RENDERER_H_
#define SLOTH_WATER_RENDERER_H_

#include "../model/raw_model.hpp"
#include "../engine/loader.h"
#include "../shader/water_shader.h"
#include "../water/water_tile.hpp"
#include "../../utils/maths.h"

namespace sloth { namespace graphics {

	class WaterRenderer
	{
	private:
		RawModel m_Quad;

	public:
		WaterRenderer(Loader &loader, const glm::mat4 &projection);

		void render(std::vector<WaterTile> &water, Camera &camera);

	private:
		void setVAO(Loader &loader);
	};

} }



#endif // !SLOTH_WATER_RENDERER_H_
