#include "particle_master.h"

sloth::ParticleMaster::ParticleMaster(Loader & loader, const glm::mat4 & projection)
	:m_Renderer(loader,projection)
{
}

void sloth::ParticleMaster::update(const RawCamera &camera)
{
	for (auto mapIt = m_Particles.begin(); mapIt != m_Particles.end(); ++mapIt) {
		auto listIt = mapIt->second->begin();
		while(listIt != mapIt->second->end()) {
			bool stillAlive = (*listIt)->update(camera);
			if (!stillAlive) { // ����������ɾ��
				auto temp = listIt;
				++listIt;
				mapIt->second->erase(temp);
			}
			else
				++listIt;
		}
		if (mapIt->second->empty()) { // �������������Ԫ�ض�ɾ����
			m_Particles.erase(mapIt);
		}
		else {
			//InsertionSort::sortHighToLow(*(mapIt->second));
		}
	}
}

void sloth::ParticleMaster::renderParticles(RawCamera & camera)
{
	m_Renderer.render(m_Particles, camera);
}

void sloth::ParticleMaster::addParticle(const std::shared_ptr<Particle>& particle)
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

