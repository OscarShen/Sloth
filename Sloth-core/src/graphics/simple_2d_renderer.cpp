#include "simple_2d_renderer.h"

namespace sloth { namespace graphics {

	void Simple2DRender::sumbit(const Renderable2D *renderable)
	{
		m_RenderQueue.push_back((StaticSprite*) renderable);
	}

	void Simple2DRender::flush()
	{
		while (!m_RenderQueue.empty())
		{
			const StaticSprite *sprite = m_RenderQueue.front();
			sprite->getVAO()->bind();
			sprite->getIBO()->bind();
			sprite->getShader().use();

			sprite->getShader().SetMatrix4("model", glm::translate(glm::mat4(), sprite->getPosition()));
			glDrawElements(GL_TRIANGLES, sprite->getIBO()->getCount(), GL_UNSIGNED_SHORT, nullptr);

			sprite->getVAO()->unbind();
			sprite->getIBO()->unbind();
			m_RenderQueue.pop_front();
		}
	}

} }
