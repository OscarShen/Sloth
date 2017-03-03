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
#ifndef SLOTH_UNIFORM_VEC4_H_
#define SLOTH_UNIFORM_VEC4_H_

#include "uniform.h"

namespace sloth { namespace graphics {

		class UniformVec4 : public Uniform
		{
		private:
			float m_X;
			float m_Y;
			float m_Z;
			float m_W;
			bool m_Used = false;

		public:
			UniformVec4(const std::string &name);

			void loadVec4(const glm::vec4 &vector);

			void loadVec4(float x, float y, float z, float w);
		};

	}
}
#endif // !SLOTH_UNIFORM_VEC4_H_