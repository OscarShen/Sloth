#include "renderable_2d.h"

namespace sloth { namespace graphics {

	void Renderable2D::submitToRenderer(Renderer2D *renderer) const
	{
		renderer->submit(this);
	}

	void Renderable2D::attachBuffer(unsigned int index, float *data, int count, unsigned int componentCount)
	{
		m_VAO->addBuffer(new Buffer(data, count, componentCount), index);
	}

	void Renderable2D::detachBuffer(unsigned int index)
	{
		m_VAO->deleteBuffer(index);
	}

	Renderable2D::~Renderable2D()
	{
		delete m_VAO;
		delete m_IBO;
	}

} }