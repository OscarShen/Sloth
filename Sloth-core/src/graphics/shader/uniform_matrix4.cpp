#include "uniform_matrix4.h"

sloth::graphics::UniformMatrix4::UniformMatrix4(const std::string &name)
	:Uniform(name)
{
}

void sloth::graphics::UniformMatrix4::loadMatrix4(const glm::mat4 & matrix)
{
	glProgramUniformMatrix4fv(Uniform::getProgramID(), Uniform::getLocation(), 1, GL_FALSE, glm::value_ptr(matrix));
}
