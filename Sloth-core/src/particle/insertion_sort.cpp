#include "insertion_sort.h"

void sloth::InsertionSort::sortHighToLow(std::list<std::shared_ptr<Particle>>& particles)
{
	for (auto it1 = particles.begin(); it1 != particles.end();)
	{
		auto it2 = it1;
		++it2;
		if (it2 != particles.end() && (*it1)->getDistance() < (*it2)->getDistance()) {
			sortUpHighToLow(particles, it2);
		}
		else {
			++it1;
		}
	}
}

void sloth::InsertionSort::sortUpHighToLow(std::list<std::shared_ptr<Particle>>& particles, std::list<std::shared_ptr<Particle>>::iterator it)
{
	auto item = *it;
	auto it2 = it;
	while (it != particles.begin()) {
		--it;
		if ((*it)->getDistance() >= item->getDistance()) {
			++it;
			break;
		}
	}
	particles.insert(it, item);
	particles.erase(it2);
}

