#include "model_loader.h"


namespace sloth { namespace graphics {

	RawModel ModelLoader::loadModel(const char * path, Loader &loader)
	{
		ModelData *modeldata = new ModelData();
		// Read file via Assimp
		Assimp::Importer importer;
		const aiScene *scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);
		// Check for errors
		if (!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
		{
			// TODO: Add to log!
			std::cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << std::endl;
			return RawModel();
		}
		processNode(modeldata, scene->mRootNode, scene);
		RawModel model = loader.loadToVAO(modeldata->positions, modeldata->texCoords,
			modeldata->normals, modeldata->indices);
		delete modeldata;
		return model;
	}

	RawModel ModelLoader::loadModelNM(const std::string & path, Loader & loader)
	{
		ModelDataNM *modeldata = new ModelDataNM();
		// Read file via Assimp
		Assimp::Importer importer;
		const aiScene *scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
		// Check for errors
		if (!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
		{
			// TODO: Add to log!
			std::cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << std::endl;
			return RawModel();
		}
		processNodeNM(modeldata, scene->mRootNode, scene);
		RawModel model = loader.loadToVAO(modeldata->positions, modeldata->texCoords,
			modeldata->normals, modeldata->tangents, modeldata->indices);
		delete modeldata;
		return model;
	}

	void ModelLoader::processNode(ModelData *modeldata, aiNode * node, const aiScene * scene)
	{
		// Process each mesh located at the current node
		for (unsigned int i = 0; i < node->mNumMeshes; ++i)
		{
			// The node object only contains indices to index the actual objects in the scene. 
			// The scene contains all the data, node is just to keep stuff organized (like relations between nodes).
			aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
			procesMesh(modeldata, mesh, scene);
		}
		// After we've processed all of the meshes (if any) we then recursively process each of the children nodes
		for (unsigned int i = 0; i < node->mNumChildren; ++i)
		{
			processNode(modeldata, node->mChildren[i], scene);
		}
	}

	void ModelLoader::procesMesh(ModelData *modeldata, aiMesh * mesh, const aiScene * scene)
	{
		// Walk through each of the mesh's vertices
		for (unsigned int i = 0; i < mesh->mNumVertices; ++i)
		{
			// Positions
			modeldata->positions.push_back(glm::vec3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z));
			// Normals
			modeldata->normals.push_back(glm::vec3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z));
			// Texture Coordinates
			if (mesh->mTextureCoords[0]) // Does the mesh contain texture coordinates?
			{
				// A vertex can contain up to 8 different texture coordinates. We thus make the assumption that we won't 
				// use models where a vertex can have multiple texture coordinates so we always take the first set (0).
				modeldata->texCoords.push_back(glm::vec2(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y));
			}
		}

		// Now wak through each of the mesh's faces (a face is a mesh its triangle) and retrieve the corresponding vertex indices.
		for (unsigned int i = 0; i < mesh->mNumFaces; ++i)
		{
			aiFace *face = mesh->mFaces + i;
			// Retrieve all indices of the face and store them in the indices vector
			for (unsigned int j = 0; j < face->mNumIndices; ++j)
			{
				// Because all vertices in a vector, index of each vertex will overlap
				modeldata->indices.push_back(face->mIndices[j]);
			}
		}
	}

	void ModelLoader::processNodeNM(ModelDataNM * modeldata, aiNode * node, const aiScene * scene)
	{
		// Process each mesh located at the current node
		for (unsigned int i = 0; i < node->mNumMeshes; ++i)
		{
			// The node object only contains indices to index the actual objects in the scene. 
			// The scene contains all the data, node is just to keep stuff organized (like relations between nodes).
			aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
			procesMeshNM(modeldata, mesh, scene);
		}
		// After we've processed all of the meshes (if any) we then recursively process each of the children nodes
		for (unsigned int i = 0; i < node->mNumChildren; ++i)
		{
			processNodeNM(modeldata, node->mChildren[i], scene);
		}
	}
	void ModelLoader::procesMeshNM(ModelDataNM * modeldata, aiMesh * mesh, const aiScene * scene)
	{
		// Walk through each of the mesh's vertices
		for (unsigned int i = 0; i < mesh->mNumVertices; ++i)
		{
			// Positions
			modeldata->positions.push_back(glm::vec3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z));
			// Normals
			modeldata->normals.push_back(glm::vec3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z));
			// Texture Coordinates
			if (mesh->mTextureCoords[0]) // Does the mesh contain texture coordinates?
			{
				// A vertex can contain up to 8 different texture coordinates. We thus make the assumption that we won't 
				// use models where a vertex can have multiple texture coordinates so we always take the first set (0).
				modeldata->texCoords.push_back(glm::vec2(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y));
			}
			modeldata->tangents.push_back(glm::vec3(mesh->mTangents[i].x, mesh->mTangents[i].y, mesh->mTangents[i].z));
		}

		// Now wak through each of the mesh's faces (a face is a mesh its triangle) and retrieve the corresponding vertex indices.
		for (unsigned int i = 0; i < mesh->mNumFaces; ++i)
		{
			aiFace *face = mesh->mFaces + i;
			// Retrieve all indices of the face and store them in the indices vector
			for (unsigned int j = 0; j < face->mNumIndices; ++j)
			{
				// Because all vertices in a vector, index of each vertex will overlap
				modeldata->indices.push_back(face->mIndices[j]);
			}
		}
	}
} }
