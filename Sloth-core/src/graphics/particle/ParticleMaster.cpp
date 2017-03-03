#include "ParticleMaster.h"

sloth::graphics::ParticleMaster::ParticleMaster(Loader & loader, const glm::mat4 & projection)
	:m_Renderer(loader,projection)
{
}

void sloth::graphics::ParticleMaster::update()
{
	for (auto it = m_Particles.begin(); it != m_Particles.end(); ) {
		bool stillAlive = (*it)->update();
		if (!stillAlive) { // 生命到期则删除
			auto temp = it;
			++it;
			m_Particles.erase(temp);
		}
		else
			++it;
	}
}

void sloth::graphics::ParticleMaster::renderParticles(RawCamera & camera)
{
	m_Renderer.render(m_Particles, camera);
}

void sloth::graphics::ParticleMaster::addParticle(const std::shared_ptr<Particle>& particle)
{
	m_Particles.push_back(particle);
}

