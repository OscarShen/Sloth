#pragma once
#ifndef SLOTH_TEXTURE_MANAGER_H_
#define SLOTH_TEXTURE_MANAGER_H_

#include <map>
#include <GL/glew.h>
#include <SOIL/SOIL.h>
#include <vector>
#include "texture_2d.h"
#include "texture_cube_map.hpp"

namespace sloth { namespace graphics {
	class Texture2D;
	class TextureManager2D
	{
	protected:
		static TextureManager2D* m_inst;
		std::map<unsigned int, Texture2D*> m_texID;
		std::map<unsigned int, TextureCubeMap*> m_CubeMaps;

	public:
		static TextureManager2D *inst();
		virtual ~TextureManager2D();

		/************************************************************************
		* @description	: 加载 cube map，输入为CubeMap的路径
		* @author		: Oscar Shen
		* @creat		: 2017年2月10日01:55:39
		***********************************************************************/
		void loadCubeMap(unsigned int cubeMapID, const std::vector<std::string> &cubeMapPaths,
			bool alpha = false, unsigned int mipmap = 0);

		/************************************************************************
		* @description	: 删除指定的 cube map
		* @author		: Oscar Shen
		* @creat		: 2017年2月10日12:16:21
		***********************************************************************/
		void unloadCubeMap(unsigned int cubeMapID);

		/************************************************************************
		* @description	: 删除所有的 cube map
		* @author		: Oscar Shen
		* @creat		: 2017年2月10日14:17:01
		***********************************************************************/
		void unloadAllCubeMap();

		/************************************************************************
		* @description	: 绑定指定的 cube map
		* @author		: Oscar Shen
		* @creat		: 2017年2月10日13:30:48
		***********************************************************************/
		void bindCubeMap(unsigned int cubeMapID);

		/************************************************************************
		* @description	: 取消绑定指定的 cube map
		* @author		: Oscar Shen
		* @creat		: 2017年2月10日13:31:52
		***********************************************************************/
		void unbindCubeMap();

		// load texture
		void loadTexture(const unsigned int texID, const char *file, bool alpha = false, unsigned int mipmap = 0);

		// set the current texture
		bool bindTexture(const unsigned int texID);

		// unbind any texutre
		bool unbindTexture();

		// free the memory for a texture
		bool unloadTexture(const unsigned int texID);

		// free all texture memory
		void unloadAllTextures();

		// activate texture unit
		bool activateTexUnit(const unsigned int index);

		// return texture pointer of texID
		Texture2D * getTexture(const unsigned int texID);

	protected:
		TextureManager2D() {}

		// Loads a single texture from file
		Texture2D* loadTextureFromFile(const GLchar *file, GLboolean alpha, GLuint mipmap);
	};
} }
#endif // !SLOTH_TEXTURE_MANAGER_H_
