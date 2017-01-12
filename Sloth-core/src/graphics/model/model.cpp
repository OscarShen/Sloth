#include "model.h"

namespace sloth { namespace graphics {
	Model::Model(const char * modelPath, const unsigned int shader)
		:Renderable(shader), m_VertexCount(0), m_IndexCount(0)
	{
		loadModel(modelPath);
	}

	Model::~Model()
	{
	}

	void Model::loadModel(const char * path)
	{
		// Read file via Assimp
		Assimp::Importer importer;
		const aiScene *scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);
		// Check for errors
		if (!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
		{
			// TODO: Add to log!
			std::cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << std::endl;
			return;
		}
		processNode(scene->mRootNode, scene);
	}

	void Model::processNode(aiNode * node, const aiScene * scene)
	{
		// Process each mesh located at the current node
		for (unsigned int i = 0; i < node->mNumMeshes; ++i)
		{
			// The node object only contains indices to index the actual objects in the scene. 
			// The scene contains all the data, node is just to keep stuff organized (like relations between nodes).
			aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
			procesMesh(mesh, scene);
		}
		// After we've processed all of the meshes (if any) we then recursively process each of the children nodes
		for (unsigned int i = 0; i < node->mNumChildren; ++i)
		{
			processNode(node->mChildren[i], scene);
		}
	}

	void Model::procesMesh(aiMesh * mesh, const aiScene * scene)
	{
		// Walk through each of the mesh's vertices
		for (unsigned int i = 0; i < mesh->mNumVertices; ++i)
		{
			// Positions
			m_Positions.push_back(glm::vec3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z));
			// Normals
			m_Normals.push_back(glm::vec3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z));
			// Texture Coordinates
			if (mesh->mTextureCoords[0]) // Does the mesh contain texture coordinates?
			{
				// A vertex can contain up to 8 different texture coordinates. We thus make the assumption that we won't 
				// use models where a vertex can have multiple texture coordinates so we always take the first set (0).
				m_TexCoords.push_back(glm::vec2(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y));
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
				m_Indices.push_back(face->mIndices[j] + m_VertexCount);
			}
		}
		// All faces are triangles
		m_IndexCount += mesh->mNumFaces * 3;

		// Size of vertices
		m_VertexCount += mesh->mNumVertices;
	}

	void Model::loadToVAO()
	{
		m_VAO = new VertexArray();
		Buffer *position = new Buffer(&m_Positions[0].x, m_VertexCount, 3);
		m_VAO->addBuffer(position, 0);
		Buffer *normal = new Buffer(&m_Normals[0].x, m_VertexCount, 3);
		m_VAO->addBuffer(normal, 3);
		if (m_TexCoords.size() > 0)
		{
			Buffer *texCoord = new Buffer(&m_TexCoords[0].x, m_VertexCount, 2);
			m_VAO->addBuffer(texCoord, 2);
		}
		IndexBuffer *indices = new IndexBuffer(&m_Indices[0], m_IndexCount);
	}


} }
