/************************************************************************ 
 * @project 	:  sloth
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
#ifndef SLOTH_WATER_TILE_H_
#define SLOTH_WATER_TILE_H_

#include "../setup/macro.h"

namespace sloth { namespace graphics {

	class WaterTile
	{
	private:
		// 水平面的高度
		float m_Height;

		float m_CenterX, m_CenterZ;

	public:
		constexpr WaterTile(float centerX, float centerZ, float height)
			:m_Height(height), m_CenterX(centerX), m_CenterZ(centerZ) {}

		inline float getHeight() const { return m_Height; }
		inline float getCenterX() const { return m_CenterX; }
		inline float getCenterZ() const { return m_CenterZ; }
	};

} }


#endif // !SLOTH_WATER_TILE_H_
