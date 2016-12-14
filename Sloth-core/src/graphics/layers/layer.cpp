#include "layer.h"
namespace sloth { namespace graphics {

	Layer::Layer(Renderer2D * renderer, Shader * shader, const glm::mat4 &projection)
		:m_Renderer(renderer),m_Shader(shader), m_Projection(projection)
	{
		m_Shader->SetMatrix4("projection", m_Projection, GL_TRUE);
	}

	Layer::~Layer()
	{
		delete m_Shader;
		delete m_Renderer;

		for (size_t i = 0; i < m_Renderables.size(); ++i)
		{
			delete m_Renderables[i];
		}
	}

	void Layer::add(Renderable2D *renderable)
	{
		m_Renderables.push_back(renderable);
	}

	void Layer::render()
	{
		for (const Renderable2D *renderable : m_Renderables)
		{
			m_Renderer->sumbit(renderable);
		}
		m_Renderer->flush();
	}

} }