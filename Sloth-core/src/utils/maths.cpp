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

	float Maths::barycentric(glm::vec3 & v1, glm::vec3 & v2, glm::vec3 & v3, glm::vec2 & pos)
	{
		float det = (v2.z - v3.z) * (v1.x - v3.x) + (v3.x - v2.x) * (v1.z - v3.z);
		float l1 = ((v2.z - v3.z) * (pos.x - v3.x) + (v3.x - v2.x) * (pos.y - v3.z)) / det;
		float l2 = ((v3.z - v1.z) * (pos.x - v3.x) + (v1.x - v3.x) * (pos.y - v3.z)) / det;
		float l3 = 1.0f - l1 - l2;
		return l1 * v1.y + l2 * v2.y + l3 * v3.y;
	}

	glm::mat4 Maths::createModelMatrix(const glm::vec2 translation, const glm::vec2 scale)
	{
		glm::mat4 matrix;
		matrix = glm::translate(matrix, glm::vec3(translation, 0.0f));
		matrix = glm::scale(matrix, glm::vec3(scale, 1.0f));
		return matrix;
	}

} }

