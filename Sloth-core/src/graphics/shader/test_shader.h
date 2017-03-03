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
#ifndef SLOTH_TEST_SHADER_H_
#define SLOTH_TEST_SHADER_H_
#include "shader.h"
namespace sloth { namespace graphics {

#define TEST_VERTEX_FILE "src/shader/test.vert"
#define TEST_FRAGMENT_FILE "src/shader/test.frag"

	class TestShader : public Shader
	{
	private:
		static TestShader *m_Inst;

		int m_LocModel;
		int m_LocView;
		int m_LocProjection;

	public:
		static TestShader *inst();

		void loadModel(const glm::mat4 &model);
		void loadView(const glm::mat4 &view);
		void loadProjection(const glm::mat4 &projection);

	private:
		TestShader();
		virtual void getAllUniformLocation() override;

	};

} }



#endif // !SLOTH_TEST_SHADER_H_
