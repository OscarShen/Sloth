#pragma once
#ifndef SLOTH_RAW_MODEL_H_
#define SLOTH_RAW_MODEL_H_


namespace sloth { namespace graphics {

	class RawModel
	{
	private:
		unsigned int m_VAO;
		unsigned int m_VertexCount;

	public:
		constexpr RawModel() :m_VAO(0), m_VertexCount(0) {}
		constexpr RawModel(unsigned int vaoID, unsigned int vertexCount) noexcept
			:m_VAO(vaoID), m_VertexCount(vertexCount) {}
		~RawModel() {}

		inline unsigned int getVaoID() const { return m_VAO; }

		inline unsigned int getVertexCount() const { return m_VertexCount; }
	};

} }


#endif // !SLOTH_RAW_MODEL_H_
