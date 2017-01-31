#include "maths.h"
namespace sloth { namespace util {
	glm::mat4 Maths::createModelMatrix(const glm::vec3 & position, float rotX, float rotY, float rotZ, float scale)
	{
		glm::mat4 model = glm::translate(glm::mat4(), position);
		model = glm::rotate(model, glm::radians(rotX), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(rotY), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(rotZ), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, glm::vec3(scale));
		return model;
	}

} }

