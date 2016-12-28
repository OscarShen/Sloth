#pragma once
#ifndef SLOTH_SHADER_H_
#define SLOTH_SHADER_H_

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <GL\glew.h>
#include "shader_manager.h"

namespace sloth {
	namespace graphics {
		class ShaderManager;
		class Shader
		{
		private:
			GLuint m_ID;
		public:
			Shader() {}
			// Compiles the shader from given source code
			void compile(const GLchar *vertexSource, const GLchar *fragmentSource, const GLchar *geometrySource = nullptr); // Note: geometry source code is optional 

			void setFloat(const GLchar *name, GLfloat value, GLboolean useShader = false);
			void setInteger(const GLchar *name, GLint value, GLboolean useShader = false);
			void setVector2f(const GLchar *name, GLfloat x, GLfloat y, GLboolean useShader = false);
			void setVector2f(const GLchar *name, const glm::vec2 &value, GLboolean useShader = false);
			void setVector3f(const GLchar *name, GLfloat x, GLfloat y, GLfloat z, GLboolean useShader = false);
			void setVector3f(const GLchar *name, const glm::vec3 &value, GLboolean useShader = false);
			void setVector4f(const GLchar *name, GLfloat x, GLfloat y, GLfloat z, GLfloat w, GLboolean useShader = false);
			void setVector4f(const GLchar *name, const glm::vec4 &value, GLboolean useShader = false);
			void setMatrix4(const GLchar *name, const glm::mat4 &matrix, GLboolean useShader = false);

			inline GLint getID() const { return this->m_ID; }

			void use() const { glUseProgram(this->m_ID); }

			void enable() const { glUseProgram(this->m_ID); }

			void disable() const { glUseProgram(0); }

		private:
			void checkCompileErrors(const GLuint shader, const std::string type);

			friend ShaderManager;
		};
	}
}
#endif // !SLOTH_SHADER_H_