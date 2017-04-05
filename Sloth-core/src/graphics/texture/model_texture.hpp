#pragma once
#ifndef SLOTH_TEXTURE_2D_H_
#define SLOTH_TEXTURE_2D_H_

#include "../../config/header.hpp"

namespace sloth { namespace graphics {
	class ModelTexture
	{
	protected:
		unsigned int m_ID;

		float m_Shininess = 128.0f;; // Shaniness
		float m_Reflectivity = 1.0f;; // Reflectivity

		bool m_HasTransparency = false;
		bool m_UseFakeLighting = false;
		bool m_HasSpecularMap = false;

		unsigned int m_NumberOfRows = 1;

		unsigned int m_NormalMap = 0;		// ∑®œﬂÃ˘Õº
		unsigned int m_SpecularMap = 0;		// ∏ﬂ¡¡Ã˘Õº
	public:
		// Constructor (sets default texture modes)
		constexpr ModelTexture() : m_ID(0) {}
		constexpr ModelTexture(unsigned int id)
			: m_ID(id) {}

		inline unsigned int getID() const { return m_ID; }
		inline float getShininess() const { return m_Shininess; }
		inline float getReflectivity() const { return m_Reflectivity; }
		inline bool hasTransparency() const { return m_HasTransparency; }
		inline bool isUseFakeLighting() const { return m_UseFakeLighting; }
		inline bool hasSpecularMap() const { return m_HasSpecularMap; }
		inline unsigned int getNumberOfRows() const { return m_NumberOfRows; }
		inline unsigned int getNormalMap() const { return m_NormalMap; }
		inline unsigned int getSpecularMap() const { return m_SpecularMap; }

		void setShininess(float shininess) { m_Shininess = shininess; }
		void setReflectivity(float reflectivity) { m_Reflectivity = reflectivity; }
		void setTransparency(bool hasTransparency) { m_HasTransparency = hasTransparency; }
		void setUseFakeLighting(bool useFakeLighting) { m_UseFakeLighting = useFakeLighting; }
		void setNumberOfRows(unsigned int numberOfRows) { m_NumberOfRows = numberOfRows; }
		void setNormalMap(unsigned int normalMap) { m_NormalMap = normalMap; }
		void setSpecularMap(int specMap) { m_SpecularMap = specMap; m_HasSpecularMap = true; }
	};

} }
#endif // !SLOTH_TEXTURE_2D_H_
