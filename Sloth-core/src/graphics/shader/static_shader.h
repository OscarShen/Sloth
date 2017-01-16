#pragma once
#ifndef SLOTH_STATIC_SHADER_H_
#define SLOTH_STATIC_SHADER_H_

#include "shader.h"
#include <glm/glm.hpp>
#include <string>
#include <vector>
#include "../entities/light.hpp"
#include "../camera/camera.h"

#define GLSL_MAX_LIGHTS 4
#define STATIC_VERTEX_FILE "src/shader/basic.vs"
#define STATIC_FRAGMENT_FILE "src/shader/basic.fs"

namespace sloth { namespace graphics {

	class StaticShader : public Shader
	{
	private:
		static StaticShader *m_inst;

		int m_LocModel;
		int m_LocView;
		int m_LocProjection;
		int *m_LocLightPos;
		int *m_LocLightColor;
		float m_LocShininess;
		float m_LocReflectivity;

	public:
		static StaticShader *inst();
		~StaticShader();
		void loadModelMatrix(const glm::mat4 &model);
		void loadViewMatrix(const Camera &camera);
		void laodProjectionMatrix(const glm::mat4 &projection);
		void loadLights(const std::vector<Light> &lights);
		void loadShineVariable(const float shininess, const float reflectivity);

	private:
		StaticShader();
		void getAllUniformLocation();
	};

} }


#endif // !SLOTH_STATIC_SHADER_H_