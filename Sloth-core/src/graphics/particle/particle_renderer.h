/************************************************************************ 
 * @project 	:  sloth
 * @class   	:  ParticleRenderer
 * @version 	:  v1.0.0
 * @description :  粒子渲染类
 * @author		:  Oscar Shen
 * @creat 		:  2017年3月6日11:17:58
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
		static const int INSTANCE_DATA_LENGTH = 21; // 当前为 21 bits

		RawModel m_Quad;
		Loader &m_Loader;
		unsigned int m_Vbo; // 用于实例化渲染
		int m_Pointer = 0; // 用于记录当前使用缓冲更新的位置

	public:
		ParticleRenderer(Loader &loader, const glm::mat4 &projection);

		void render(const std::unordered_map<ParticleTexture, std::shared_ptr<std::list<std::shared_ptr<Particle>>>> & particles, RawCamera &camera);

	private:
		void prepare();

		/************************************************************************
		* @description	: 绑定并设置 particle texture 有关的属性
		* @author		: Oscar Shen
		* @creat		: 2017年3月8日22:13:45
		***********************************************************************/
		void bindTexture(const ParticleTexture &texture);

		/************************************************************************
		* @description	: 计算并在 vbo 中更新 modelView 矩阵，位置由 pointer 成员指定
		* @author		: Oscar Shen
		* @creat		: 2017年3月8日22:14:34
		***********************************************************************/
		void updateModelView(const glm::vec3 &position, float rotation, float scale, const glm::mat4 &view, std::vector<float>& vboData);

		/************************************************************************
		* @description	: 在 vbo 中更新纹理相关数据如 texCoordNow, texCoordNext, blendFactor，
						  位置由 pointer 成员指定
		* @author		: Oscar Shen
		* @creat		: 2017年3月8日22:15:41
		***********************************************************************/
		void updateTexCoordInfo(const Particle &particle, std::vector<float> &data);

		/************************************************************************
		* @description	: 将计算得到的 modelView 矩阵更新到 vbo 中
		* @author		: Oscar Shen
		* @creat		: 2017年3月8日22:16:28
		***********************************************************************/
		void storeMatrixDataInVbo(const glm::mat4 &matrix, std::vector<float> &vboData);

		void unbind();
	};

} }


#endif // !SLOTH_PARTICLE_RENDERER_H_
