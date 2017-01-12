#pragma once
#ifndef SLOTH_MODEL_H_
#define SLOTH_MODEL_H_

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <string>
#include <vector>

#include "../renderable/renderable.h"

using std::vector;
namespace sloth { namespace graphics {
	class Model : public Renderable
	{
	private:
		vector<glm::vec3> m_Positions;
		vector<glm::vec2> m_TexCoords;
		vector<glm::vec3> m_Normals;
		vector<unsigned int> m_Indices;
		unsigned int m_VertexCount;
		unsigned int m_IndexCount;

	public:
		Model(const char *modelPath, const unsigned int shader);
		virtual ~Model();

	private:
		// Loads a model with supported ASSIMP extensions from file and stores the resulting meshes in the meshes vector.
		void loadModel(const char *path);
		// Processes a node in a recursive fashion. Processes each individual mesh located at the node and repeats this process on its children nodes (if any).
		void processNode(aiNode *node, const aiScene *scene);
		
		void procesMesh(aiMesh *mesh, const aiScene *scene);

		void loadToVAO();
	};

} }



#endif // !SLOTH_MODEL_H_
