#pragma once
#ifndef SLOTH_STATIC_SHADER_H_
#define SLOTH_STATIC_SHADER_H_

#include "shader.h"
#include <glm/glm.hpp>
#include <string>
#include <vector>
#include "../entities/light.hpp"
#include "../camera/camera.h"
#include "../setup/macro.h"

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
		int m_LocShininess;
		int m_LocReflectivity;
		int m_LocUseFakeLighting;
		int m_LocSkyColor;
		int m_LocNumberOfRows;
		int m_LocOffset;

	public:
		static StaticShader *inst();
		~StaticShader();
		virtual void loadModelMatrix(const glm::mat4 &model) override;
		virtual void loadViewMatrix(const RawCamera &camera) override;
		virtual void loadProjectionMatrix(const glm::mat4 &projection) override;
		virtual void loadLight(const Light &light) override;
		virtual void loadLights(const std::vector<Light> &lights) override;
		virtual void loadShineVariable(const float shininess, const float reflectivity) override;
		virtual void loadUseFakeLighting(const bool useFake) override;
		virtual void loadSkyColor(const float r, const float g, const float b);
		virtual void loadNumberOfRows(int numberOfRaws);
		virtual void loadOffset(float x, float y);


	private:
		StaticShader();

	protected:
		virtual void getAllUniformLocation() override;
	};

} }


#endif // !SLOTH_STATIC_SHADER_H_
