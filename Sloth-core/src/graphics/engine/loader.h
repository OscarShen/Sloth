/************************************************************************
 * @project 	:  sloth
 * @class   	:  Loader
 * @version 	:  v1.0.0
 * @description :  所有的VAO都需要由 Loader 类来加载至 OpenGL。换言之，所有的
				   RawModel 只能由 Loader 来生成
 * @author		:  Oscar Shen
 * @creat 		:  2017年2月13日21:54:09
 * @revise 		:
************************************************************************
 * Copyright @ OscarShen 2017. All rights reserved.
************************************************************************/
#pragma once
#ifndef SLOTH_LOADER_H_
#define SLOTH_LOADER_H_

#include <GL/glew.h>
#include <vector>
#include <glm/glm.hpp>
#include <SOIL/SOIL.h>
#include "../buffers/index_buffer.h"
#include "../buffers/vertex_array.h"
#include "../model/raw_model.hpp"
#include "../model/model_data.hpp"
#include "../../config/header.hpp"

namespace sloth { namespace graphics {

	class Loader
	{
	private:
		std::vector<VertexArray*> m_Vaos1;
		std::vector<unsigned int> m_Textures;

	public:
		Loader() {}
		~Loader();

		/************************************************************************
		* @description	: 输入3维位置、2维纹理、3维法向量、以及顶点索引
		* @author		: Oscar Shen
		* @creat		: 2017年2月16日10:00:40
		***********************************************************************/
		RawModel loadToVAO(
			std::vector<glm::vec3> &positions,
			std::vector<glm::vec2> &texCoords,
			std::vector<glm::vec3> &normals,
			std::vector<unsigned int> &indices
		);

		/************************************************************************
		* @description	: 建立一个只包含vec2位置和纹理的RawModel，主要用于建立二维GUI矩形
		* @author		: Oscar Shen
		* @creat		: 2017年2月9日14:03:57
		***********************************************************************/
		RawModel loadToVAO(
			std::vector<glm::vec2> &positions,
			std::vector<glm::vec2> &texCoords
		);

		/************************************************************************
		* @description	: 建立一个只包含vec3位置的RawModel
		* @author		: Oscar Shen
		* @creat		: 2017年2月9日14:03:57
		***********************************************************************/
		RawModel loadToVAO(
			std::vector<glm::vec3> &positions
		);

		/************************************************************************
		* @description	: 建立一个只包含dimention位置的RawModel
		* @author		: Oscar Shen
		* @creat		: 2017年2月13日18:56:46
		***********************************************************************/
		RawModel loadToVAO(
			std::vector<float> &position,
			int dimention
		);

		/************************************************************************
		* @description	: 加载二维纹理
		* @author		: Oscar Shen
		* @creat		: 2017年2月13日18:56:46
		***********************************************************************/
		unsigned int loadTexture(const std::string &fileName, bool alpha = false);

		/************************************************************************
		* @description	: 加载立方体纹理
		* @author		: Oscar Shen
		* @creat		: 2017年2月13日18:56:46
		***********************************************************************/
		unsigned int loadCubeMap(const std::vector<std::string> &cubeMapPaths, bool alpha = false);

		/************************************************************************
		* @description	: 清除当前 Loader 加载的所有资源
		* @author		: Oscar Shen
		* @creat		: 2017年2月16日10:02:02
		***********************************************************************/
		void cleanUp();

	private:
		VertexArray* createVAO();

		unsigned int setupTexture(int width, int height, unsigned char *data, bool alpha);
	};


} }


#endif // !SLOTH_LOADER_H_
