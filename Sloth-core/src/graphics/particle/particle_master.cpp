#include "particle_master.h"

sloth::graphics::ParticleMaster::ParticleMaster(Loader & loader, const glm::mat4 & projection)
	:m_Renderer(loader,projection)
{
}

void sloth::graphics::ParticleMaster::update()
{
	for (auto mapIt = m_Particles.begin(); mapIt != m_Particles.end(); ++mapIt) {
		auto listIt = mapIt->second->begin();
		while(listIt != mapIt->second->end()) {
			bool stillAlive = (*listIt)->update();
			if (!stillAlive) { // 生命到期则删除
				auto temp = listIt;
				++listIt;
				mapIt->second->erase(temp);
			}
			else
				++listIt;
		}
		if (mapIt->second->empty()) { // 如果容器中所有元素都删除了
			m_Particles.erase(mapIt);
		}
	}
}

void sloth::graphics::ParticleMaster::renderParticles(RawCamera & camera)
{
	//for(auto it = m_Particles.begin(); it!=m_Particles.end();++it)
	//	m_Renderer.render(*(it->second), camera);
	m_Renderer.render(m_Particles, camera);
}

void sloth::graphics::ParticleMaster::addParticle(const std::shared_ptr<Particle>& particle)
{
	auto it = m_Particles.find(particle->getTexture());
	if (it != m_Particles.end()) {
		it->second->push_back(particle);
	}
	else {
		auto list = std::shared_ptr<std::list<std::shared_ptr<Particle>>>(new std::list<std::shared_ptr<Particle>>());
		list->push_back(particle);
		m_Particles[particle->getTexture()] = list;
	}
}

