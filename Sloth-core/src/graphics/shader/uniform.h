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
#ifndef SLOTH_UNIFORM_H_
#define SLOTH_UNIFORM_H_

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <string>

namespace sloth { namespace graphics {

	class Uniform
	{
	private:
		static const int NOT_FOUND = -1;
		std::string m_Name; // ������
		int m_Location; // OpenGL λ��
		unsigned int m_ProgramID; // ������һ�� shader ����

	public:
		Uniform(const std::string &name);

		void storeUniformLocation(unsigned int programID);

		inline int getLocation() const { return m_Location; }

		inline unsigned int getProgramID() const { return m_ProgramID; }
	};

} }



#endif // !SLOTH_UNIFORM_H_
