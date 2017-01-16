#pragma once
#ifndef SLOTH_TEXTURED_MODEL_H_
#define SLOTH_TEXTURED_MODEL_H_

#include "raw_model.hpp"
namespace sloth { namespace graphics {

	class TexturedModel
	{
	private:
		RawModel m_RawModel;
		unsigned int m_TexID;

	public:
		constexpr TexturedModel(const RawModel &rawModel, unsigned int texID)
			:m_RawModel(rawModel), m_TexID(texID) {}

		inline RawModel getRawModel() const { return m_RawModel; }
		inline unsigned int getTexID() const { return m_TexID; }

		friend bool operator<(const TexturedModel &left, const TexturedModel &right);
	};

} }


#endif // !SLOTH_TEXTURED_MODEL_H_
