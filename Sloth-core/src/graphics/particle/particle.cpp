#include "particle.h"

bool sloth::graphics::Particle::update()
{
	float deltaTime = static_cast<float>(util::Timer::deltaFrameTime);
	m_Velocity.y += PLAYER_GRAVITY * m_GravityEffect * deltaTime;
	m_Position += m_Velocity * deltaTime;
	m_ElapsedTime += deltaTime;
	updateTextureCoordInfo();
	return m_ElapsedTime < m_LifeLength;
}

void sloth::graphics::Particle::updateTextureCoordInfo()
{
	float lifeFactor = m_ElapsedTime / m_LifeLength;
	unsigned int stageCount = m_Texture.getNumberOfRows() * m_Texture.getNumberOfRows(); // 获取所有纹理集的个数
	float atlasProgression = lifeFactor * stageCount; // 当前处理的纹理序号
	unsigned int indexNow = static_cast<unsigned int>(glm::floor(atlasProgression));
	unsigned int indexNext = indexNow < stageCount - 1 ? indexNow + 1 : indexNow;
	m_BlendFactor = std::fmodf(atlasProgression, 1.0f); // 根据时间再两个状态间进行插值
	setTextureOffset(m_TexOffsetNow, indexNow);
	setTextureOffset(m_TexOffsetNext, indexNext);
}

void sloth::graphics::Particle::setTextureOffset(glm::vec2 & offset, unsigned int index)
{
	unsigned int column = index % m_Texture.getNumberOfRows();
	unsigned int row = index / m_Texture.getNumberOfRows();
	offset.x = static_cast<float>(column) / m_Texture.getNumberOfRows();
	offset.y = static_cast<float>(row) / m_Texture.getNumberOfRows();
}
