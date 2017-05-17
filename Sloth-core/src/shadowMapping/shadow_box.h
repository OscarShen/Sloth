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
#ifndef SLOTH_SHADOW_BOX_H_
#define SLOTH_SHADOW_BOX_H_
#include <sloth.h>

namespace sloth { 

	class ShadowBox
	{
	private:
		static const float OFFSET;
		static const glm::vec4 UP;
		static const glm::vec4 FORWARD;
		static const float SHADOW_DISTANCE;

		float m_MinX, m_MaxX;
		float m_MinY, m_MaxY;
		float m_MinZ, m_MaxZ;
		glm::mat4 m_LightView;
		RawCamera &m_Camera;

		float m_FarWidth, m_NearWidth, m_FarHeight, m_NearHeight;

	public:
		ShadowBox(const glm::mat4 &lightView, RawCamera &camera);
		void update();

	private:
		void calculateWidthAndHeight();
		glm::mat4 calculateCameraRotation();
	};

} 



#endif // !SLOTH_SHADOW_BOX_H_
