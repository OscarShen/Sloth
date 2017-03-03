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
#ifndef SLOTH_UNIFORM_VEC2_H_
#define SLOTH_UNIFORM_VEC2_H_

#include "uniform.h"

namespace sloth { namespace graphics {

		class UniformVec2 : public Uniform
		{
		private:
			float m_X;
			float m_Y;
			bool m_Used = false;

		public:
			UniformVec2(const std::string &name);

			void loadVec2(const glm::vec2 &vector);

			void loadVec2(float x, float y);
		};

	}
}
#endif // !SLOTH_UNIFORM_VEC2_H_