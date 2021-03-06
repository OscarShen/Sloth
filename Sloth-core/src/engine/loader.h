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

#include <sloth.h>
#include <buffers/index_buffer.h>
#include <buffers/vertex_array.h>
#include <model/raw_model.hpp>
#include <model/model_data.hpp>
#include <config/header.hpp>

namespace sloth {

	class Loader
	{
	private:
		std::vector<VertexArray*> m_Vaos1;
		std::vector<unsigned int> m_Textures;
		std::vector<unsigned int> m_Vbos;

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
		* @description	: 输入3维位置、2维纹理
		* @author		: Oscar Shen
		* @creat		: 2017年3月2日11:14:40
		***********************************************************************/
		RawModel loadToVAO(
			std::vector<glm::vec3> &positions,
			std::vector<glm::vec2> &texCoords
		);

		/************************************************************************
		* @description	: 输入2维位置、2维纹理，返回VAO句柄
		* @author		: Oscar Shen
		* @creat		: 2017年2月27日22:03:05
		***********************************************************************/
		unsigned int loadToVAO(
			std::vector<float> &positions,
			std::vector<float> &texCoords
			);


		/************************************************************************
		* @description	: 输入3维位置、2维纹理、3维法向量、3维正切坐标以及顶点索引
		* @author		: Oscar Shen
		* @creat		: 2017年2月16日10:00:40
		***********************************************************************/
		RawModel loadToVAO(
			std::vector<glm::vec3> &positions,
			std::vector<glm::vec2> &texCoords,
			std::vector<glm::vec3> &normals,
			std::vector<glm::vec3> &tangents,
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
		* @description	: 创建一个指定大小的 vbo，大小指定后不可变更
		* @author		: Oscar Shen
		* @creat		: 2017年3月8日22:04:37
		***********************************************************************/
		unsigned int createEmptyVbo(unsigned int floatCount);

		/************************************************************************
		* @description	: 用于实例渲染的属性数据组织
						  vao : 需要将数据绑定到的 vao
						  vbo : 存储实例数据的缓冲
						  attribute : 当前组织的属性编号
						  dataSize : vao 该属性对应的向量大小，vec2->2，vec4->4
						  instancedDataLength : 单个实例的总数据长度
						  offset : 这个属性在总数据中的字节起始位置
		* @author		: Oscar Shen
		* @creat		: 2017年3月8日22:09:40
		***********************************************************************/
		void addIntancedAttribute(unsigned int vao, unsigned int vbo, unsigned int attribute,
			unsigned int dataSize, unsigned int instancedDataLength, unsigned int offset);

		/************************************************************************
		* @description	: 将组织好的数据导入 vbo
		* @author		: Oscar Shen
		* @creat		: 2017年3月8日22:10:16
		***********************************************************************/
		void updateVbo(unsigned int vbo, std::vector<float> &vboData);

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


}


#endif // !SLOTH_LOADER_H_
