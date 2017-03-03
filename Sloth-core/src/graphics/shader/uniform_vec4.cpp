#include "uniform_vec4.h"

sloth::graphics::UniformVec4::UniformVec4(const std::string & name)
	: Uniform(name)
{
}

void sloth::graphics::UniformVec4::loadVec4(const glm::vec4 & vector)
{
	loadVec4(vector.x, vector.y, vector.z, vector.w);
}

void sloth::graphics::UniformVec4::loadVec4(float x, float y, float z, float w)
{
	if (!m_Used || m_X != x || m_Y != y || m_Z != z) {
		m_X = x;
		m_Y = y;
		m_Z = z;
		m_W = w;
		glProgramUniform4f(Uniform::getProgramID(), Uniform::getLocation(), x, y, z, w);
		m_Used = true;
	}
}
