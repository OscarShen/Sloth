#pragma once
#ifndef SLOTH_TERRAIN_SHADER_H_
#define SLOTH_TERRAIN_SHADER_H_

#include "shader.h"
#include "../setup/macro.h"

namespace sloth { namespace graphics {

	class TerrainShader : public Shader
	{
	private:
		static TerrainShader *m_Inst;

		int m_LocModel;
		int m_LocView;
		int m_LocProjection;
		int *m_LocLightPos;
		int *m_LocLightColor;
		int m_LocShininess;
		int m_LocReflectivity;
		int m_LocSkyColor;
		int m_LocBackgroundTexture;
		int m_LocRTexture;
		int m_LocGTexture;
		int m_LocBTexture;
		int m_LocBlendMapTexture;


	public:
		~TerrainShader();
		static TerrainShader* inst();
		virtual void loadModelMatrix(const glm::mat4 &model) override;
		virtual void loadViewMatrix(const RawCamera &camera) override;
		virtual void loadProjectionMatrix(const glm::mat4 &projection) override;
		virtual void loadLight(const Light &light) override;
		virtual void loadLights(const std::vector<Light> &lights) override;
		virtual void loadShineVariable(const float shininess, const float reflectivity) override;
		virtual void loadSkyColor(const float r, const float g, const float b);
		virtual void connectTextureUnits();

	private:
		TerrainShader();

	protected:
		virtual void getAllUniformLocation() override;
	};

} }


#endif // !SLOTH_TERRAIN_SHADER_H_
