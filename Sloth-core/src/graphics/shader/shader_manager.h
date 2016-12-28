#pragma once
#ifndef SLOTH_SHADER_MANAGER_H_
#define SLOTH_SHADER_MANAGER_H_

#include <map>
#include <GL/glew.h>
#include "shader.h"

namespace sloth { namespace graphics {
	class Shader;
	class ShaderManager
	{
	protected:
		static ShaderManager* m_inst;
		std::map<unsigned int, Shader*> m_shaderID;

	public:
		static ShaderManager* inst();
		virtual ~ShaderManager();

		// load shader
		void loadShader(unsigned int shaderID, const GLchar *vShaderFile, const GLchar *fShaderFile, const GLchar *gShaderFile=nullptr);

		// set current shader
		bool use(const unsigned int shaderID);

		// disuse any shader
		bool disuse(const unsigned int shaderID);

		// free the memory for a shader
		bool unloadShader(const unsigned int shaderID);

		// free all shader memory
		void unloadAllShaders();

		// return shader pointer of shaderID
		Shader* getShader(const unsigned int shaderID);
		
	protected:
		ShaderManager() {}

		// load a single shader from file
		Shader* loadTextureFromFile(const GLchar *vShaderFile, const GLchar *fShaderFile, const GLchar *gShaderFile = nullptr);
	};

} }

#endif // !SLOTH_SHADER_MANAGER_H_
