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
#include <vector>

#include <GL/glew.h>

#include "../../utils/string_util.h"
#include "../entities/light.hpp"
#include "../camera/camera.h"

namespace sloth { namespace graphics {

	class RawCamera;
	struct Light;
	class Shader
	{
	protected:
		unsigned int m_ID;
	public:
		Shader(const char *vertexPath, const char *fragmentPath, const char *geometryPath = nullptr);
		virtual ~Shader() {}

		void loadFloat(const char *name, float value);
		void loadInteger(const char *name, int value);
		void loadVector2f(const char *name, float x, float y);
		void loadVector2f(const char *name, const glm::vec2 &value);
		void loadVector3f(const char *name, float x, float y, float z);
		void loadVector3f(const char *name, const glm::vec3 &value);
		void loadVector4f(const char *name, float x, float y, float z, float w);
		void loadVector4f(const char *name, const glm::vec4 &value);
		void loadMatrix4(const char *name, const glm::mat4 &matrix);
		void loadMatrix4(int location, const glm::mat4 &matrix);

		inline unsigned int getID() const { return this->m_ID; }

		void use() const { glUseProgram(this->m_ID); }

		void enable() const { glUseProgram(this->m_ID); }

		void disable() const { glUseProgram(0); }

	private:
		void checkCompileErrors(const GLuint shader, const std::string type);

		// Compiles the shader from given source code
		void compile(const char *vertexSource, const char *fragmentSource, const char *geometrySource); // Note: geometry source code is optional 

	protected:
		// 获取所有与 GUI 相关的 uniform 变量地址，
		// 在构造器中调用一次即可
		virtual void getAllUniformLocation() {}
	};
} }
#endif // !SLOTH_SHADER_H_