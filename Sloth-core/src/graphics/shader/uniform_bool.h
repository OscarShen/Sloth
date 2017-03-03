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
#ifndef SLOTH_UNIFORM_BLOOL_H_
#define SLOTH_UNIFORM_BLOOL_H_

#include "uniform.h"

namespace sloth { namespace graphics {

	class UniformBool : public Uniform
	{
	private:
		bool m_CurrentBool;
		bool m_Used = false;

	public:
		UniformBool(const std::string &name);

		void loadBool(bool b);
	};

} }


#endif // !SLOTH_UNIFORM_BLOOL_H_
