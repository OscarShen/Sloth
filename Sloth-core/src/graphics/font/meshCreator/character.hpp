/************************************************************************ 
 * @project 	:  sloth
 * @class   	:  Character
 * @version 	:  v1.0.0
 * @description :  �洢������Ⱦ����Ҫ��������Ϣ
 * @author		:  Oscar Shen
 * @creat 		:  2017��2��27��21:22:29
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
		* @description	: �洢������Ϣ
						  id : ����� ASCII ֵ
						  xMin : ������������x����Сֵ
						  yMin : ������������y����Сֵ
						  xTexSize : ����������
						  yTexSize : ��������߶�
						  xOffset : �����α굽x������ߵľ���
						  yOffset : �����α굽y�����ϱߵľ���
						  width : ���巽��Ŀ��
						  height : ���巽��ĸ߶�
						  xAdvance : ���ӱ�������Ҫǰ�������ظ���
		* @author		: Oscar Shen
		* @creat		: 2017��2��22��20:02:23
		***********************************************************************/
		constexpr Character(unsigned int id, double xMin, double yMin, double xTexSize, double yTexSize,
			double xOffset, double yOffset,
			double width, double height, double xAdvance)
			: m_ID(id), m_XMin(xMin), m_YMin(yMin), m_XMax(xTexSize + xMin),
			m_YMax(yTexSize + yMin), m_XOffset(xOffset), m_YOffset(yOffset),
			m_Width(width), m_Height(height), m_XAdvance(xAdvance) {}

		/***********************************************************************
		* @description	: ��������� ASCII ֵ
		* @author		: Oscar Shen
		* @creat		: 2017��2��27��21:22:59
		***********************************************************************/
		inline unsigned int getID() const { return m_ID; }

		/***********************************************************************
		* @description	: ����������������x����Сֵ
		* @author		: Oscar Shen
		* @creat		: 2017��2��27��21:22:59
		***********************************************************************/
		inline double getXMin() const { return m_XMin; }

		/***********************************************************************
		* @description	: ����������������x�����ֵ
		* @author		: Oscar Shen
		* @creat		: 2017��2��27��21:22:59
		***********************************************************************/
		inline double getXMax() const { return m_XMax; }

		/***********************************************************************
		* @description	: ����������������y����Сֵ
		* @author		: Oscar Shen
		* @creat		: 2017��2��27��21:22:59
		***********************************************************************/
		inline double getYMin() const { return m_YMin; }

		/***********************************************************************
		* @description	: ����������������y�����ֵ
		* @author		: Oscar Shen
		* @creat		: 2017��2��27��21:22:59
		***********************************************************************/
		inline double getYMax() const { return m_YMax; }

		/***********************************************************************
		* @description	: ����������Ⱦ��Ҫ�������α�x�������
		* @author		: Oscar Shen
		* @creat		: 2017��2��27��21:22:59
		***********************************************************************/
		inline double getXOffset() const { return m_XOffset; }

		/***********************************************************************
		* @description	: ����������Ⱦ��Ҫ�������α�y�������
		* @author		: Oscar Shen
		* @creat		: 2017��2��27��21:22:59
		***********************************************************************/
		inline double getYOffset() const { return m_YOffset; }

		/***********************************************************************
		* @description	: �������巽������Ļ�ռ�ĸ߶�
		* @author		: Oscar Shen
		* @creat		: 2017��2��27��21:22:59
		***********************************************************************/
		inline double getHeight() const { return m_Height; }

		/***********************************************************************
		* @description	: �������巽������Ļ�ռ�Ŀ��
		* @author		: Oscar Shen
		* @creat		: 2017��2��27��21:22:59
		***********************************************************************/
		inline double getWidth() const { return m_Width; }

		/***********************************************************************
		* @description	: ����������Ⱦ�����������
		* @author		: Oscar Shen
		* @creat		: 2017��2��27��21:22:59
		***********************************************************************/
		inline double getXAdvance() const { return m_XAdvance; }
	};
} }

#endif // !SLOTH_CHARACTER_HPP
