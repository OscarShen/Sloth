/************************************************************************ 
 * @project 	:  sloth
 * @class   	:  Character
 * @version 	:  v1.0.0
 * @description :  存储字体渲染所需要的纹理信息
 * @author		:  Oscar Shen
 * @creat 		:  2017年2月27日21:22:29
 * @revise 		:  
************************************************************************ 
 * Copyright @ OscarShen 2017. All rights reserved. 
************************************************************************/  
#pragma once
#ifndef SLOTH_CHARACTER_HPP
#define SLOTH_CHARACTER_HPP

namespace sloth { namespace graphics {

	class Character
	{
		unsigned int m_ID;
		double m_XMin;
		double m_YMin;
		double m_XMax;
		double m_YMax;
		double m_XOffset;
		double m_YOffset;
		double m_Width;
		double m_Height;
		double m_XAdvance;

	public:
		/***********************************************************************
		* @description	: 存储字体信息
						  id : 字体的 ASCII 值
						  xMin : 字体纹理坐标x轴最小值
						  yMin : 字体纹理坐标y轴最小值
						  xTexSize : 字体纹理宽度
						  yTexSize : 字体纹理高度
						  xOffset : 字体游标到x轴最左边的距离
						  yOffset : 字体游标到y轴最上边的距离
						  width : 字体方块的宽度
						  height : 字体方块的高度
						  xAdvance : 增加本字体如要前进的像素个数
		* @author		: Oscar Shen
		* @creat		: 2017年2月22日20:02:23
		***********************************************************************/
		constexpr Character(unsigned int id, double xMin, double yMin, double xTexSize, double yTexSize,
			double xOffset, double yOffset,
			double width, double height, double xAdvance)
			: m_ID(id), m_XMin(xMin), m_YMin(yMin), m_XMax(xTexSize + xMin),
			m_YMax(yTexSize + yMin), m_XOffset(xOffset), m_YOffset(yOffset),
			m_Width(width), m_Height(height), m_XAdvance(xAdvance) {}

		/***********************************************************************
		* @description	: 返回字体的 ASCII 值
		* @author		: Oscar Shen
		* @creat		: 2017年2月27日21:22:59
		***********************************************************************/
		inline unsigned int getID() const { return m_ID; }

		/***********************************************************************
		* @description	: 返回字体纹理坐标x轴最小值
		* @author		: Oscar Shen
		* @creat		: 2017年2月27日21:22:59
		***********************************************************************/
		inline double getXMin() const { return m_XMin; }

		/***********************************************************************
		* @description	: 返回字体纹理坐标x轴最大值
		* @author		: Oscar Shen
		* @creat		: 2017年2月27日21:22:59
		***********************************************************************/
		inline double getXMax() const { return m_XMax; }

		/***********************************************************************
		* @description	: 返回字体纹理坐标y轴最小值
		* @author		: Oscar Shen
		* @creat		: 2017年2月27日21:22:59
		***********************************************************************/
		inline double getYMin() const { return m_YMin; }

		/***********************************************************************
		* @description	: 返回字体纹理坐标y轴最大值
		* @author		: Oscar Shen
		* @creat		: 2017年2月27日21:22:59
		***********************************************************************/
		inline double getYMax() const { return m_YMax; }

		/***********************************************************************
		* @description	: 返回字体渲染需要调整的游标x方向距离
		* @author		: Oscar Shen
		* @creat		: 2017年2月27日21:22:59
		***********************************************************************/
		inline double getXOffset() const { return m_XOffset; }

		/***********************************************************************
		* @description	: 返回字体渲染需要调整的游标y方向距离
		* @author		: Oscar Shen
		* @creat		: 2017年2月27日21:22:59
		***********************************************************************/
		inline double getYOffset() const { return m_YOffset; }

		/***********************************************************************
		* @description	: 返回字体方块在屏幕空间的高度
		* @author		: Oscar Shen
		* @creat		: 2017年2月27日21:22:59
		***********************************************************************/
		inline double getHeight() const { return m_Height; }

		/***********************************************************************
		* @description	: 返回字体方块在屏幕空间的宽度
		* @author		: Oscar Shen
		* @creat		: 2017年2月27日21:22:59
		***********************************************************************/
		inline double getWidth() const { return m_Width; }

		/***********************************************************************
		* @description	: 返回字体渲染后产生的缩进
		* @author		: Oscar Shen
		* @creat		: 2017年2月27日21:22:59
		***********************************************************************/
		inline double getXAdvance() const { return m_XAdvance; }
	};
} }

#endif // !SLOTH_CHARACTER_HPP
