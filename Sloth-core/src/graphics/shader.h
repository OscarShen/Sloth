//#pragma once
//#ifndef SLOTH_SHADER_H_
//#define SLOTH_SHADER_H_
//
//#include <string>
//
//#include <GL/glew.h>
//#include <glm/glm.hpp>
//#include <glm/gtc/type_ptr.hpp>
//
//
//// General purpsoe shader object. Compiles from file, generates
//// compile/link-time error messages and hosts several utility 
//// functions for easy management.
//namespace sloth {
//	namespace graphics {
//		class Shader
//		{
//		public:
//			// State
//			GLuint ID;
//			// Constructor
//			Shader() { }
//			// Sets the current shader as active
//			Shader  &Use();
//			// Compiles the shader from given source code
//			void    Compile(const GLchar *vertexSource, const GLchar *fragmentSource, const GLchar *geometrySource = nullptr); // Note: geometry source code is optional 
//																															   // Utility functions
//			void    SetFloat(const GLchar *name, GLfloat value, GLboolean useShader = false);
//			void    SetInteger(const GLchar *name, GLint value, GLboolean useShader = false);
//			void    SetVector2f(const GLchar *name, GLfloat x, GLfloat y, GLboolean useShader = false);
//			void    SetVector2f(const GLchar *name, const glm::vec2 &value, GLboolean useShader = false);
//			void    SetVector3f(const GLchar *name, GLfloat x, GLfloat y, GLfloat z, GLboolean useShader = false);
//			void    SetVector3f(const GLchar *name, const glm::vec3 &value, GLboolean useShader = false);
//			void    SetVector4f(const GLchar *name, GLfloat x, GLfloat y, GLfloat z, GLfloat w, GLboolean useShader = false);
//			void    SetVector4f(const GLchar *name, const glm::vec4 &value, GLboolean useShader = false);
//			void    SetMatrix4(const GLchar *name, const glm::mat4 &matrix, GLboolean useShader = false);
//		private:
//			// Checks if compilation or linking failed and if so, print the error logs
//			void    checkCompileErrors(GLuint object, std::string type);
//		};
//	}
//}
//#endif

#pragma once
#ifndef SHADER_H_
#define SHADER_H_

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <GL\glew.h>

namespace sloth {
	namespace graphics {
		class Shader
		{
		public:
			GLint program;
			Shader(const GLchar* vertexPath, const GLchar* fragmentPath, const GLchar* geometryPath = nullptr) {
				std::string vertexCode;
				std::string fragmentCode;
				std::string geometryCode;
				std::ifstream vShaderFile;
				std::ifstream fShaderFile;
				std::ifstream gShaderFile;

				// ensure ifsream objects can throw exceptions
				vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
				fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
				gShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
				try {
					// Open files
					vShaderFile.open(vertexPath);
					fShaderFile.open(fragmentPath);
					std::stringstream vShaderStream, fShaderStream;
					// Read file's buffer contents into streams
					vShaderStream << vShaderFile.rdbuf();
					fShaderStream << fShaderFile.rdbuf();
					// Close file handlers
					vShaderFile.close();
					fShaderFile.close();
					// Convert stream into string
					vertexCode = vShaderStream.str();
					fragmentCode = fShaderStream.str();

					// If we can load a geometry shader
					if (geometryPath != nullptr) {
						gShaderFile.open(geometryPath);
						std::stringstream gShaderStream;
						gShaderStream << gShaderFile.rdbuf();
						gShaderFile.close();
						geometryCode = gShaderStream.str();
					}
				}
				catch (std::ifstream::failure e) {
					std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
				}
				const GLchar *vShaderCode = vertexCode.c_str();
				const GLchar *fShaderCode = fragmentCode.c_str();
				// Compile
				GLuint vertex, fragment, geometry;
				// Vertex Shader
				vertex = glCreateShader(GL_VERTEX_SHADER);
				glShaderSource(vertex, 1, &vShaderCode, nullptr);
				glCompileShader(vertex);
				checkCompileErrors(vertex, "VERTEX");
				// Fragment Shader
				fragment = glCreateShader(GL_FRAGMENT_SHADER);
				glShaderSource(fragment, 1, &fShaderCode, nullptr);
				glCompileShader(fragment);
				checkCompileErrors(fragment, "FRAGMENT");
				// Geometry Shader
				if (geometryPath != nullptr) {
					const GLchar *gShaderCode = geometryCode.c_str();
					geometry = glCreateShader(GL_GEOMETRY_SHADER);
					glShaderSource(geometry, 1, &gShaderCode, nullptr);
					glCompileShader(geometry);
					checkCompileErrors(geometry, "GEOMETRY");
				}

				// Shader program
				this->program = glCreateProgram();
				glAttachShader(this->program, vertex);
				glAttachShader(this->program, fragment);
				if (geometryPath != nullptr)
					glAttachShader(this->program, geometry);
				glLinkProgram(this->program);
				checkCompileErrors(this->program, "PROGRAM");
				// Delete shaders after linked into program
				glDeleteShader(vertex);
				glDeleteShader(fragment);
				if (geometryPath != nullptr)
					glDeleteShader(geometry);
			}

			void    SetFloat(const GLchar *name, GLfloat value, GLboolean useShader = false);
			void    SetInteger(const GLchar *name, GLint value, GLboolean useShader = false);
			void    SetVector2f(const GLchar *name, GLfloat x, GLfloat y, GLboolean useShader = false);
			void    SetVector2f(const GLchar *name, const glm::vec2 &value, GLboolean useShader = false);
			void    SetVector3f(const GLchar *name, GLfloat x, GLfloat y, GLfloat z, GLboolean useShader = false);
			void    SetVector3f(const GLchar *name, const glm::vec3 &value, GLboolean useShader = false);
			void    SetVector4f(const GLchar *name, GLfloat x, GLfloat y, GLfloat z, GLfloat w, GLboolean useShader = false);
			void    SetVector4f(const GLchar *name, const glm::vec4 &value, GLboolean useShader = false);
			void    SetMatrix4(const GLchar *name, const glm::mat4 &matrix, GLboolean useShader = false);


			inline void use() const { glUseProgram(this->program); }

			inline void enable() const { glUseProgram(this->program); }

			inline void disable() const { glUseProgram(0); }

			~Shader();

		private:
			void checkCompileErrors(const GLuint shader, const std::string type) {
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
		};
	}
}
#endif // !SHADER_H_