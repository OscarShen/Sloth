#include "shader_manager.h"

namespace sloth { namespace graphics {
	ShaderManager* ShaderManager::m_inst(nullptr);

	ShaderManager * ShaderManager::inst()
	{
		if (!m_inst)
			m_inst = new ShaderManager();
		return m_inst;
	}

	ShaderManager::~ShaderManager()
	{
		unloadAllShaders();
		m_inst = nullptr;
	}

	void ShaderManager::loadShader(unsigned int shaderID, const GLchar * vShaderFile, const GLchar * fShaderFile, const GLchar * gShaderFile)
	{
		if (m_shaderID.find(shaderID) != m_shaderID.end())
			unloadShader(shaderID);
		m_shaderID[shaderID] = loadTextureFromFile(vShaderFile, fShaderFile, gShaderFile);
	}

	bool ShaderManager::use(const unsigned int shaderID)
	{
		bool result(true);
		//if this shader ID mapped, use it's shader as current
		if (m_shaderID.find(shaderID) != m_shaderID.end())
			glUseProgram(m_shaderID[shaderID]->getID());
		//otherwise, using failed
		else
			result = false;

		return result;
	}

	bool ShaderManager::disuse(const unsigned int shaderID)
	{
		bool result(true);
		glUseProgram(0);
		return result;
	}

	bool ShaderManager::unloadShader(const unsigned int shaderID)
	{
		bool result(true);
		//if this shader ID mapped, unload it's shader, and remove it from the map
		if (m_shaderID.find(shaderID) != m_shaderID.end())
		{
			glDeleteShader(m_shaderID[shaderID]->getID());
			delete m_shaderID[shaderID];
			m_shaderID.erase(shaderID);
		}
		//otherwise, unload failed
		else
		{
			result = false;
		}

		return result;
	}

	void ShaderManager::unloadAllShaders()
	{
		//start at the begginning of the texture map
		auto i = m_shaderID.begin();
		//Unload the textures untill the end of the texture map is found
		while (i != m_shaderID.end())
		{
			auto j = i;
			i++;
			unloadShader(j->first);
		}

		//clear the texture map
		m_shaderID.clear();
	}

	Shader * ShaderManager::getShader(const unsigned int shaderID)
	{
		Shader * result(nullptr);
		if (m_shaderID.find(shaderID) != m_shaderID.end())
			result = m_shaderID[shaderID];
		return result;
	}

	Shader * ShaderManager::loadTextureFromFile(const GLchar * vShaderFile, const GLchar * fShaderFile, const GLchar * gShaderFile)
	{
		// 1. Retrieve the vertex/fragment source code from filePath
		std::string vertexCode;
		std::string fragmentCode;
		std::string geometryCode;
		try
		{
			// Open files
			std::ifstream vertexShaderFile(vShaderFile);
			std::ifstream fragmentShaderFile(fShaderFile);
			std::stringstream vShaderStream, fShaderStream;
			// Read file's buffer contents into streams
			vShaderStream << vertexShaderFile.rdbuf();
			fShaderStream << fragmentShaderFile.rdbuf();
			// close file handlers
			vertexShaderFile.close();
			fragmentShaderFile.close();
			// Convert stream into string
			vertexCode = vShaderStream.str();
			fragmentCode = fShaderStream.str();
			// If geometry shader path is present, also load a geometry shader
			if (gShaderFile != nullptr)
			{
				std::ifstream geometryShaderFile(gShaderFile);
				std::stringstream gShaderStream;
				gShaderStream << geometryShaderFile.rdbuf();
				geometryShaderFile.close();
				geometryCode = gShaderStream.str();
			}
		}
		catch (std::exception e)
		{
			std::cout << "ERROR::SHADER: Failed to read shader files" << std::endl;
		}
		const GLchar *vShaderCode = vertexCode.c_str();
		const GLchar *fShaderCode = fragmentCode.c_str();
		const GLchar *gShaderCode = geometryCode.c_str();
		// 2. Now create shader object from source code
		Shader *shader = new Shader();
		shader->compile(vShaderCode, fShaderCode, gShaderFile != nullptr ? gShaderCode : nullptr);
		return shader;
	}

} }

