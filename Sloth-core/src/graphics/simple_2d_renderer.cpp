#include "simple_2d_renderer.h"

namespace sloth { namespace graphics {

	void Simple2DRender::sumbit(const Renderable2D *renderable)
	{
		m_RenderQueue.push_back(renderable);
	}

	void Simple2DRender::flush()
	{
		while (!m_RenderQueue.empty())
		{
			const Renderable2D *renderable = m_RenderQueue.front();
			renderable->getVAO()->bind();
			renderable->getIBO()->bind();
			renderable->getShader()->use();

			renderable->getShader()->SetMatrix4("model", glm::translate(glm::mat4(), renderable->getPosition()));
			glDrawElements(GL_TRIANGLES, renderable->getIBO()->getCount(), GL_UNSIGNED_SHORT, nullptr);

			renderable->getVAO()->unbind();
			renderable->getIBO()->unbind();
			m_RenderQueue.pop_front();
		}
	}

} }
