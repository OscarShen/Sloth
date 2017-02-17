#pragma once
#ifndef SLOTH_TEXTURED_MODEL_H_
#define SLOTH_TEXTURED_MODEL_H_

#include "raw_model.hpp"
#include "../texture/model_texture.hpp"
namespace sloth { namespace graphics {

	class TexturedModel
	{
	private:
		RawModel m_RawModel;
		ModelTexture m_Texture;

	public:	
		constexpr explicit TexturedModel(const RawModel &rawModel, const ModelTexture &texture)
			:m_RawModel(rawModel), m_Texture(texture) {}

		inline const RawModel& getRawModel() const { return m_RawModel; }
		inline const ModelTexture& getTexture() const { return m_Texture; }

		friend bool operator<(const TexturedModel &left, const TexturedModel &right);
	};
} }


#endif // !SLOTH_TEXTURED_MODEL_H_
