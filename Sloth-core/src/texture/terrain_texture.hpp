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
#ifndef SLOTH_TERRAIN_TEXTURE_H_
#define SLOTH_TERRAIN_TEXTURE_H_

#include <sloth.h>
namespace sloth {

	class TerrainTexture
	{
	private:
		unsigned int m_ID;

	public:

		TerrainTexture(unsigned int id) :m_ID(id) {}

		inline unsigned int getID() const { return m_ID; }
	};

} 
#endif // !SLOTH_TERRAIN_TEXTURE_H_
