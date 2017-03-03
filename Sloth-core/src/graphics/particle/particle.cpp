#include "particle.h"

bool sloth::graphics::Particle::update()
{
	float deltaTime = static_cast<float>(util::Timer::deltaFrameTime);
	m_Velocity.y += PLAYER_GRAVITY * m_GravityEffect * deltaTime;
	m_Position += m_Velocity * deltaTime;
	m_ElapsedTime += deltaTime;
	return m_ElapsedTime < m_LifeLength;
}
