/************************************************************************ 
 * @project 	:  sloth
 * @class   	:  WaterTile
 * @version 	:  v1.0.0
 * @description :  记录着水面的位置和高度
 * @author		:  Oscar Shen
 * @creat 		:  2017年2月13日21:59:43
 * @revise 		:  
************************************************************************ 
 * Copyright @ OscarShen 2017. All rights reserved. 
************************************************************************/  
#pragma once
#ifndef SLOTH_WATER_TILE_H_
#define SLOTH_WATER_TILE_H_

namespace sloth { namespace graphics {

	class WaterTile
	{
	private:
		// 水平面的高度
		float m_Height;
		// 水面中心
		float m_CenterX, m_CenterZ;

	public:
		/***********************************************************************
		* @description	: 构造 WaterTile，centerX 和 centerY 表示水面中心的世界坐标，
						  height 表示水面的高度
		* @author		: Oscar Shen
		* @creat		: 2017年2月13日21:54:54
		***********************************************************************/
		constexpr WaterTile(float centerX, float centerZ, float height)
			:m_Height(height), m_CenterX(centerX), m_CenterZ(centerZ) {}

		inline float getHeight() const { return m_Height; }
		inline float getCenterX() const { return m_CenterX; }
		inline float getCenterZ() const { return m_CenterZ; }
	};

} }


#endif // !SLOTH_WATER_TILE_H_
