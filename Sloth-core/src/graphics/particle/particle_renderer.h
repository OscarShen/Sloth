/************************************************************************ 
 * @project 	:  sloth
 * @class   	:  ParticleRenderer
 * @version 	:  v1.0.0
 * @description :  ������Ⱦ��
 * @author		:  Oscar Shen
 * @creat 		:  2017��3��6��11:17:58
 * @revise 		:  
************************************************************************ 
 * Copyright @ OscarShen 2017. All rights reserved. 
************************************************************************/  
#pragma once
#ifndef SLOTH_PARTICLE_RENDERER_H_
#define SLOTH_PARTICLE_RENDERER_H_
#include <vector>
#include <list>
#include <unordered_map>
#include "../model/raw_model.hpp"
#include "../engine/loader.h"
#include "particle_shader.h"
#include "particle.h"
namespace sloth { namespace graphics {
	class ParticleRenderer
	{
	private:
		static std::vector<float> VERTICES;
		static const int MAX_INSTANCES = 10000;
		static const int INSTANCE_DATA_LENGTH = 21; // ��ǰΪ 21 bits

		RawModel m_Quad;
		Loader &m_Loader;
		unsigned int m_Vbo; // ����ʵ������Ⱦ
		int m_Pointer = 0; // ���ڼ�¼��ǰʹ�û�����µ�λ��

	public:
		ParticleRenderer(Loader &loader, const glm::mat4 &projection);

		void render(const std::unordered_map<ParticleTexture, std::shared_ptr<std::list<std::shared_ptr<Particle>>>> & particles, RawCamera &camera);

	private:
		void prepare();

		/************************************************************************
		* @description	: �󶨲����� particle texture �йص�����
		* @author		: Oscar Shen
		* @creat		: 2017��3��8��22:13:45
		***********************************************************************/
		void bindTexture(const ParticleTexture &texture);

		/************************************************************************
		* @description	: ���㲢�� vbo �и��� modelView ����λ���� pointer ��Աָ��
		* @author		: Oscar Shen
		* @creat		: 2017��3��8��22:14:34
		***********************************************************************/
		void updateModelView(const glm::vec3 &position, float rotation, float scale, const glm::mat4 &view, std::vector<float>& vboData);

		/************************************************************************
		* @description	: �� vbo �и���������������� texCoordNow, texCoordNext, blendFactor��
						  λ���� pointer ��Աָ��
		* @author		: Oscar Shen
		* @creat		: 2017��3��8��22:15:41
		***********************************************************************/
		void updateTexCoordInfo(const Particle &particle, std::vector<float> &data);

		/************************************************************************
		* @description	: ������õ��� modelView ������µ� vbo ��
		* @author		: Oscar Shen
		* @creat		: 2017��3��8��22:16:28
		***********************************************************************/
		void storeMatrixDataInVbo(const glm::mat4 &matrix, std::vector<float> &vboData);

		void unbind();
	};

} }


#endif // !SLOTH_PARTICLE_RENDERER_H_
