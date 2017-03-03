#include "uniform_vec2.h"

sloth::graphics::UniformVec2::UniformVec2(const std::string & name)
	:Uniform(name)
{
}

void sloth::graphics::UniformVec2::loadVec2(const glm::vec2 & vector)
{
	loadVec2(vector.x, vector.y);
}

void sloth::graphics::UniformVec2::loadVec2(float x, float y)
{
	if (!m_Used || x != m_X || y != m_Y) {
		glProgramUniform2f(Uniform::getProgramID(), Uniform::getLocation(), x, y);
		m_X = x;
		m_Y = y;
		m_Used = true;
	}
}

