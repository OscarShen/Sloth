#pragma once
#ifndef SLOTH_TEXTURED_MODEL_H_
#define SLOTH_TEXTURED_MODEL_H_
#include <sloth.h>
#include "raw_model.hpp"
#include <texture/model_texture.hpp>
#include <unordered_map>
namespace sloth {

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
		friend bool operator==(const TexturedModel &left, const TexturedModel &right);
	};
} 

namespace std {
	template <>
	struct hash<sloth::TexturedModel> {
		std::size_t operator()(const sloth::TexturedModel& model) const {
			return model.getRawModel().getVertexCount() * 31 + model.getRawModel().getVaoID() * 131
				+ model.getTexture().getID() * 97;
		}
	};
}


#endif // !SLOTH_TEXTURED_MODEL_H_
