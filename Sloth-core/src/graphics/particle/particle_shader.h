/************************************************************************ 
 * @project 	:  sloth
 * @class   	:  ParticleShader
 * @version 	:  v1.0.0
 * @description :  粒子着色器操作类
 * @author		:  Oscar Shen
 * @creat 		:  2017年3月6日11:18:52
 * @revise 		:  
************************************************************************ 
 * Copyright @ OscarShen 2017. All rights reserved. 
************************************************************************/  
#pragma once
#ifndef SLOTH_PARTICLE_SHADER_H_
#define SLOTH_PARTICLE_SHADER_H_
#include <memory>
#include "../shader/shader.h"
#include "../shader/uniform_matrix4.h"
#include "../shader/uniform_float.h"
namespace sloth { namespace graphics {

#define PARTICLE_VERTEX_SHADER "src/graphics/particle/particle.vert"
#define PARTICLE_FRAGMENT_SHADER "src/graphics/particle/particle.frag"

	class ParticleShader : public Shader
	{
	private:
		static std::shared_ptr<ParticleShader> m_Inst;

	public:
		UniformMatrix4 projection = UniformMatrix4("projection");
		UniformMatrix4 modelView = UniformMatrix4("modelView");
		
		static std::shared_ptr<ParticleShader> inst();

	private:
		ParticleShader();
	};

} }

#endif // !SLOTH_PARTICLE_SHADER_H_
