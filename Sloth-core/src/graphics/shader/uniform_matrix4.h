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
#ifndef SLOTH_UNIFORM_MATRIX4_H_
#define SLOTH_UNIFORM_MATRIX4_H_
#include "uniform.h"
#include <glm/gtc/type_ptr.hpp>
namespace sloth { namespace graphics {

	class UniformMatrix4 : public Uniform
	{
	public:
		UniformMatrix4(const std::string &name);

		void loadMatrix4(const glm::mat4 &matrix);
	};

} }

#endif // !SLOTH_UNIFORM_MATRIX4_H_
