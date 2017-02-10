/************************************************************************ 
 * @project 	:  sloth
 * @class   	:  SkyboxRenderer
 * @version 	:  v1.0.0
 * @description :  skybox ����Ⱦ������
 * @author		:  Oscar Shen
 * @creat 		:  2017��2��10��17:26:09
 * @revise 		:  
************************************************************************ 
 * Copyright @ OscarShen 2017. All rights reserved. 
************************************************************************/  
#pragma once
#ifndef SLOTH_SKYBOX_RENDERER_H_
#define SLOTH_SKYBOX_RENDERER_H_

#include <glm/glm.hpp>
#include <vector>
#include <string>
#include "../shader/skybox_shader.h"
#include "../engine/loader.h"
#include "../model/raw_model.hpp"
#include "../camera/raw_camera.h"

namespace sloth { namespace graphics {

	class SkyboxRenderer
	{
	private:
		static float m_Size;
		static std::vector<glm::vec3> m_Vertices;

		RawModel m_Cube;

	public:
		SkyboxRenderer() {}
		~SkyboxRenderer() {}

		/***********************************************************************
		* @description	: ������պ�renderer
						  cubeMapID : ��Ҫ��Ⱦ����պ��Զ�����
						  loader	: sloth���е�VAO���� loader ����
		* @author		: Oscar Shen
		* @creat		: 2017��2��10��14:00:24
		***********************************************************************/
		SkyboxRenderer(Loader &loader, const glm::mat4 &projection);

		/***********************************************************************
		* @description	: ��Ⱦ��պ�
		* @author		: Oscar Shen
		* @creat		: 2017��2��10��16:27:13
		***********************************************************************/
		void render(unsigned int cubeMapID, const RawCamera &camera);
	};

} }


#endif // !SLOTH_SKYBOX_RENDERER_H_
