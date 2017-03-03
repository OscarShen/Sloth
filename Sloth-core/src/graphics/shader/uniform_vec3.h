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
#ifndef SLOTH_UNIFORM_VEC3_H_
#define SLOTH_UNIFORM_VEC3_H_

#include "uniform.h"

namespace sloth { namespace graphics {

	class UniformVec3 : public Uniform
	{
	private:
		float m_X;
		float m_Y;
		float m_Z;
		bool m_Used = false;

	public:
		UniformVec3(const std::string &name);

		void loadVec3(const glm::vec3 &vector);

		void loadVec3(float x, float y, float z);
	};

} }
#endif // !SLOTH_UNIFORM_VEC3_H_