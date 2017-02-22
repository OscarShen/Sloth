/************************************************************************
* @project 		:  sloth
* @class   		:  ModelDataNM
* @version 		:  v1.0.0
* @description	:  记录包含法线贴图的模型数据结构
* @author		:  Oscar Shen
* @creat 		:  2017年2月21日21:34:41
* @revise 		:
************************************************************************
* Copyright @ OscarShen 2017. All rights reserved.
************************************************************************/
#pragma once
#ifndef SLOTH_MODEL_LOADER_H_
#define SLOTH_MODEL_LOADER_H_

#include "../model/raw_model.hpp"
#include "../model/model_data.hpp"
#include "../model/model_data_NM.hpp"
#include "loader.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <string>

#include <iostream>
namespace sloth { namespace graphics {

	class ModelLoader
	{
	public:
		// Loads a model with supported ASSIMP extensions from file and stores the resulting meshes in the meshes vector.
		static RawModel loadModel(const char *path, Loader &loader);

		static RawModel loadModelNM(const std::string &path, Loader &loader);

	private:
		// Processes a node in a recursive fashion. Processes each individual mesh located at the node and repeats this process on its children nodes (if any).
		static void processNode(ModelData *modeldata, aiNode *node, const aiScene *scene);

		static void procesMesh(ModelData *modeldata, aiMesh *mesh, const aiScene *scene);

		// Processes a node in a recursive fashion. Processes each individual mesh located at the node and repeats this process on its children nodes (if any).
		static void processNodeNM(ModelDataNM *modeldata, aiNode *node, const aiScene *scene);

		static void procesMeshNM(ModelDataNM *modeldata, aiMesh *mesh, const aiScene *scene);

	};

} }


#endif // !SLOTH_MODEL_LOADER_H_
