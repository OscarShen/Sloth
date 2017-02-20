/************************************************************************ 
 * @project 	:  sloth
 * @class   	:  WaterTile
 * @version 	:  v1.0.0
 * @description :  ��¼��ˮ���λ�ú͸߶�
 * @author		:  Oscar Shen
 * @creat 		:  2017��2��13��21:59:43
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
		// ˮƽ��ĸ߶�
		float m_Height;
		// ˮ������
		float m_CenterX, m_CenterZ;

	public:
		/***********************************************************************
		* @description	: ���� WaterTile��centerX �� centerY ��ʾˮ�����ĵ��������꣬
						  height ��ʾˮ��ĸ߶�
		* @author		: Oscar Shen
		* @creat		: 2017��2��13��21:54:54
		***********************************************************************/
		constexpr WaterTile(float centerX, float centerZ, float height)
			:m_Height(height), m_CenterX(centerX), m_CenterZ(centerZ) {}

		inline float getHeight() const { return m_Height; }
		inline float getCenterX() const { return m_CenterX; }
		inline float getCenterZ() const { return m_CenterZ; }
	};

} }


#endif // !SLOTH_WATER_TILE_H_
