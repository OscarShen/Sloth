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
#ifndef SLOTH_UNIFORM_SAMPLER_H_
#define SLOTH_UNIFORM_SAMPLER_H_

#include "uniform.h"

namespace sloth { namespace graphics {

	class UniformSampler : public Uniform
	{
	private:
		int m_CurrentValue;
		bool m_Used = false;

	public:
		UniformSampler(const std::string &name);

		void loadTexUnit(int texUnit);
	};

} }
#endif // !SLOTH_UNIFORM_SAMPLER_H_