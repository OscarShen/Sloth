#include "shader.h"

#include <iostream>

namespace sloth {
	namespace graphics {

		void Shader::compile(const GLchar * vertexSource, const GLchar * fragmentSource, const GLchar * geometrySource)
		{
			GLuint sVertex, sFragment, gShader;
			// Vertex Shader
			sVertex = glCreateShader(GL_VERTEX_SHADER);
			glShaderSource(sVertex, 1, &vertexSource, NULL);
			glCompileShader(sVertex);
			checkCompileErrors(sVertex, "VERTEX");
			// Fragment Shader
			sFragment = glCreateShader(GL_FRAGMENT_SHADER);
			glShaderSource(sFragment, 1, &fragmentSource, NULL);
			glCompileShader(sFragment);
			checkCompileErrors(sFragment, "FRAGMENT");
			// If geometry shader source code is given, also compile geometry shader
			if (geometrySource != nullptr)
			{
				gShader = glCreateShader(GL_GEOMETRY_SHADER);
				glShaderSource(gShader, 1, &geometrySource, NULL);
				glCompileShader(gShader);
				checkCompileErrors(gShader, "GEOMETRY");
			}
			// Shader Program
			m_ID = glCreateProgram();
			glAttachShader(m_ID, sVertex);
			glAttachShader(m_ID, sFragment);
			if (geometrySource != nullptr)
				glAttachShader(m_ID, gShader);
			glLinkProgram(m_ID);
			checkCompileErrors(m_ID, "PROGRAM");
			// Delete the shaders as they're linked into our m_ID now and no longer necessery
			glDeleteShader(sVertex);
			glDeleteShader(sFragment);
			if (geometrySource != nullptr)
				glDeleteShader(gShader);
		}

		void Shader::setFloat(const GLchar *name, GLfloat value, GLboolean useShader)
		{
			if (useShader) {
				this->enable();
				glUniform1f(glGetUniformLocation(this->m_ID, name), value);
				this->disable();
			}
			else {
				glUniform1f(glGetUniformLocation(this->m_ID, name), value);
			}
		}
		void Shader::setInteger(const GLchar *name, GLint value, GLboolean useShader)
		{
			if (useShader)
				this->enable();
			glUniform1i(glGetUniformLocation(this->m_ID, name), value);
		}
		void Shader::setVector2f(const GLchar *name, GLfloat x, GLfloat y, GLboolean useShader)
		{
			if (useShader)
				this->enable();
			glUniform2f(glGetUniformLocation(this->m_ID, name), x, y);
		}
		void Shader::setVector2f(const GLchar *name, const glm::vec2 &value, GLboolean useShader)
		{
			if (useShader)
				this->enable();
			glUniform2f(glGetUniformLocation(this->m_ID, name), value.x, value.y);
		}
		void Shader::setVector3f(const GLchar *name, GLfloat x, GLfloat y, GLfloat z, GLboolean useShader)
		{
			if (useShader)
				this->enable();
			glUniform3f(glGetUniformLocation(this->m_ID, name), x, y, z);
		}
		void Shader::setVector3f(const GLchar *name, const glm::vec3 &value, GLboolean useShader)
		{
			if (useShader)
				this->enable();
			glUniform3f(glGetUniformLocation(this->m_ID, name), value.x, value.y, value.z);
		}
		void Shader::setVector4f(const GLchar *name, GLfloat x, GLfloat y, GLfloat z, GLfloat w, GLboolean useShader)
		{
			if (useShader)
				this->enable();
			glUniform4f(glGetUniformLocation(this->m_ID, name), x, y, z, w);
		}
		void Shader::setVector4f(const GLchar *name, const glm::vec4 &value, GLboolean useShader)
		{
			if (useShader)
				this->enable();
			glUniform4f(glGetUniformLocation(this->m_ID, name), value.x, value.y, value.z, value.w);
		}
		void Shader::setMatrix4(const GLchar *name, const glm::mat4 &matrix, GLboolean useShader)
		{
			if (useShader)
				this->enable();
			glUniformMatrix4fv(glGetUniformLocation(this->m_ID, name), 1, GL_FALSE, glm::value_ptr(matrix));
		}

		void Shader::checkCompileErrors(const GLuint shader, const std::string type)
		{
			GLint success;
			GLchar infoLog[1024];
			if (type != "PROGRAM") {
				glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
				if (!success) {
					glGetShaderInfoLog(shader, 1024, nullptr, infoLog);
					std::cout << "| ERROR::::SHADER-COMPILATION-ERROR of type: " << type << "|\n" << infoLog << "\n| -- --------------------------------------------------- -- |" << std::endl;
				}
			}
			else {
				glGetProgramiv(shader, GL_LINK_STATUS, &success);
				if (!success) {
					glGetProgramInfoLog(shader, 1024, nullptr, infoLog);
					std::cout << "| ERROR::::PROGRAM-LINKING-ERROR of type: " << type << "|\n" << infoLog << "\n| -- --------------------------------------------------- -- |" << std::endl;
				}
			}
		}
	}
}