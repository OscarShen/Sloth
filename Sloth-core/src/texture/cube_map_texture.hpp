/************************************************************************ 
 * @project 	:  sloth
 * @class   	:  CubeMapTexture
 * @version 	:  v1.0.0
 * @description :  封装 cube map
 * @author		:  Oscar Shen
 * @creat 		:  2017年2月10日11:41:55
 * @revise 		:  
************************************************************************ 
 * Copyright @ OscarShen 2017. All rights reserved. 
************************************************************************/  
#pragma once
#ifndef SLOTH_TEXTURE_CUBE_MAP_H_
#define SLOTH_TEXTURE_CUBE_MAP_H_

#include <sloth.h>

namespace sloth {

	class CubeMapTexture
	{
	private:
		unsigned int m_ID;

	public:
		constexpr CubeMapTexture(unsigned int id) : m_ID(id) {}
		
		inline unsigned int getID() const { return m_ID; }
		void setID(unsigned int glID) { m_ID = glID; }
	};
} 

#endif // !SLOTH_TEXTURE_CUBE_MAP_H_
