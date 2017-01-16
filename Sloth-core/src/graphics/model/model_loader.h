#pragma once
#ifndef SLOTH_MODEL_LOADER_H_
#define SLOTH_MODEL_LOADER_H_

#include "raw_model.hpp"
#include "model_data.hpp"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <iostream>
namespace sloth { namespace graphics {

	class ModelLoader
	{
	public:
		// Loads a model with supported ASSIMP extensions from file and stores the resulting meshes in the meshes vector.
		static ModelData* loadModel(const char *path);

		// If you do not release model data, it will released.
		static void releaseModelData(ModelData *modeldata);

	private:
		// Processes a node in a recursive fashion. Processes each individual mesh located at the node and repeats this process on its children nodes (if any).
		static void processNode(ModelData *modeldata, aiNode *node, const aiScene *scene);

		static void procesMesh(ModelData *modeldata, aiMesh *mesh, const aiScene *scene);
	};



} }


#endif // !SLOTH_MODEL_LOADER_H_
