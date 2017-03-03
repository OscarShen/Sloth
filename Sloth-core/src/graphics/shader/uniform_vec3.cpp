#include "uniform_vec3.h"

sloth::graphics::UniformVec3::UniformVec3(const std::string & name)
	:Uniform(name)
{
}

void sloth::graphics::UniformVec3::loadVec3(const glm::vec3 & vector)
{
	loadVec3(vector.x, vector.y, vector.z);
}

void sloth::graphics::UniformVec3::loadVec3(float x, float y, float z)
{
	if (!m_Used || x != m_X || y != m_Y || z != m_Z) {
		m_X = x;
		m_Y = y;
		m_Z = z;
		m_Used = true;
		glProgramUniform3f(Uniform::getProgramID(), Uniform::getLocation(), m_X, m_Y, m_Z);
	}
}
