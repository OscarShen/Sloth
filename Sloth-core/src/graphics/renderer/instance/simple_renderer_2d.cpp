#include "simple_renderer_2d.h"

namespace sloth { namespace graphics {

	void SimpleRenderer2D::flush()
	{
		auto sm = ShaderManager::inst();
		while (!m_RenderQueue.empty())
		{
			auto sprite = m_RenderQueue.front();
			sprite->getVAO()->bind();
			sprite->getIBO()->bind();
			auto shaderID = sprite->getShader();
			sm->getShader(shaderID)->setMatrix4("model", *backMatrix(), true);

			glDrawElements(GL_TRIANGLES, sprite->getIBO()->getCount(), GL_UNSIGNED_SHORT, nullptr);

			sprite->getVAO()->unbind();
			sprite->getIBO()->unbind();
			m_RenderQueue.pop_front();
		}
	}

	void SimpleRenderer2D::submit(const Renderable2D * renderable)
	{
		m_RenderQueue.push_back(renderable);
	}

} }
