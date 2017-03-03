#include "uniform.h"

sloth::graphics::Uniform::Uniform(const std::string & name)
	:m_Name(name)
{
}

void sloth::graphics::Uniform::storeUniformLocation(unsigned int programID)
{
	m_ProgramID = programID;
	m_Location = glGetUniformLocation(programID, m_Name.c_str());
	if (m_Location == NOT_FOUND)
		printf("No uniform variable called %s found!", m_Name);
}
