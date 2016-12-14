#include "tile_layer.h"

namespace sloth { namespace graphics {

	TileLayer::TileLayer(Shader * shader)
		: Layer(new BatchRenderer2D(), shader, glm::ortho(-16.0f, 16.0f, -12.0f, 12.0f, -1.0f, 1.0f))
	{
	}

	TileLayer::~TileLayer()
	{
	}

	void TileLayer::render()
	{
		m_Renderer->begin();
		for (const Renderable2D *renderable : m_Renderables)
		{
			m_Renderer->sumbit(renderable);
		}
		m_Renderer->end();
		m_Renderer->flush();
	}

} }
