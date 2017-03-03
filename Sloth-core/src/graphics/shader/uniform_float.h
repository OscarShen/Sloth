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
#ifndef SLOTH_UNIFORM_FLOAT_H_
#define SLOTH_UNIFORM_FLOAT_H_

#include "uniform.h"

namespace sloth { namespace graphics {

		class UniformFloat : public Uniform
		{
		private:
			float m_CurrentValue;
			bool m_Used = false;

		public:
			UniformFloat(const std::string &name);

			void loadFloat(float value);
		};

	}
}


#endif // !SLOTH_UNIFORM_FLOAT_H_