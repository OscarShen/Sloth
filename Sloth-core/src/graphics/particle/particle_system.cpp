#include "particle_system.h"

namespace sloth { namespace graphics {

	void ParticleSystem::generateParticles(const glm::vec3 &systemCenter, ParticleMaster &particleMaster)
	{
		float delta = static_cast<float>(util::Timer::deltaFrameTime);
		float particlesToCreate = m_ParticlesPerSecond * delta;
		int count = static_cast<int>(glm::floor(particlesToCreate));
		float partialParticle = std::fmodf(particlesToCreate, 1.0f);
		for (int i = 0; i < count; ++i) {
			emitParticle(systemCenter, particleMaster);
		}
		if (partialParticle > 0.5f) { // 如果残留的粒子大于一半，就发射出去
			emitParticle(systemCenter, particleMaster);
		}
	}

	void ParticleSystem::emitParticle(const glm::vec3 &center, ParticleMaster &particleMaster)
	{
		glm::vec3 velocity;
		if (m_Direction != glm::vec3(0.0f)) {
			velocity = glm::normalize(generateRandomUnitVectorWithinCone(m_Direction, m_DirectionDeviation));
		}
		else {
			velocity = glm::normalize(generateRandomUnitVector());
		}
		velocity *= generateValue(m_AverageSpeed, m_SpeedError);
		float scale = generateValue(m_AverageScale, m_ScaleError);
		float lifeLength = generateValue(m_AverageLifeLength, m_LifeError);
		particleMaster.addParticle(std::make_shared<Particle>(center, velocity, m_GravityComplient, lifeLength, generateRotation(), scale));
	}

	float ParticleSystem::generateValue(float average, float errorMargin)
	{
		float offset = (rand() / static_cast<float>(RAND_MAX) - 0.5f) * 2.0f * errorMargin;
		return average + offset;
	}

	float ParticleSystem::generateRotation()
	{
		return m_RandomRotation ? (rand() / static_cast<float>(RAND_MAX)) * 360.0f : 0.0f;
	}

	glm::vec3 ParticleSystem::generateRandomUnitVectorWithinCone(const glm::vec3 & coneDirection, float angle)
	{
		float cosAngle = glm::cos(angle);
		float theta = (rand() / static_cast<float>(RAND_MAX)) * glm::two_pi<float>();
		float z = cosAngle + (rand() / static_cast<float>(RAND_MAX) * (1 - cosAngle));
		float rootOneMinusZSquared = glm::sqrt(1.0f - z*z);
		float x = rootOneMinusZSquared * glm::cos(theta);
		float y = rootOneMinusZSquared * glm::sin(theta);

		glm::vec4 direction(x, y, z, 1.0f);
		if (coneDirection.x != 0.0f || coneDirection.y != 0.0f || (coneDirection.z != 1.0f && coneDirection.z != -1.0f)) {
			glm::vec3 &&rotateAxis = glm::normalize(glm::cross(coneDirection, glm::vec3(0.0f, 0.0f, 1.0f)));
			float rotateAngle = glm::acos(glm::dot(coneDirection, glm::vec3(0.0f, 0.0f, 1.0f)));
			glm::mat4 &&rotationMatrix = glm::rotate(-rotateAngle, rotateAxis);
			direction = rotationMatrix * direction;
		}
		else if (coneDirection.z == -1.0f) {
			direction.z *= -1.0f;
		}
		return glm::vec3(direction);
	}

	glm::vec3 ParticleSystem::generateRandomUnitVector()
	{
		float theta = (rand() / static_cast<float>(RAND_MAX)) * glm::two_pi<float>();
		float z = (rand() / static_cast<float>(RAND_MAX)) * 2.0f - 1.0f;
		float rootOneMinusZSquared = glm::sqrt(1.0f - z*z);
		float x = rootOneMinusZSquared * glm::cos(theta);
		float y = rootOneMinusZSquared * glm::sin(theta);
		return glm::vec3(x, y, z);
	}

} }