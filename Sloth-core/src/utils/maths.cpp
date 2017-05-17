#include "maths.h"
namespace sloth { 
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

	glm::vec3 Maths::rayPlaneIntersection(const glm::vec3 & ray_origin, const glm::vec3 & ray_dir, const glm::vec3 & p1, const glm::vec3 & p2, const glm::vec3 & p3)
	{
		// e + td = x + β(y − x) + γ(z − x)
		// x = m_QuadLT, y = m_QuadLD, z = m_QuadRD
		// 光线与三角形平面投影，克拉默法则
		float a = p1.x - p2.x;
		float b = p1.y - p2.y;
		float c = p1.z - p2.z;
		float d = p1.x - p3.x;
		float e = p1.y - p3.y;
		float f = p1.z - p3.z;
		float g = ray_dir.x;
		float h = ray_dir.y;
		float i = ray_dir.z;
		float j = p1.x - ray_origin.x;
		float k = p1.y - ray_origin.y;
		float l = p1.z - ray_origin.z;

		float M = a*(e*i - h*f) + b*(g*f - d*i) + c*(d*h - e*g);
		//float beta = (j*(e*i - h*f) + k*(g*f - d*i) + l*(d*h - e*g)) / M;
		//float gamma = (i*(a*k - j*b) + h*(j*c - a*l) + g*(b*l - k*c))/M;
		float t = -(f*(a*k - j*b) + e*(j*c - a*l) + d*(b*l - k*c)) / M;
		return ray_origin + ray_dir*t;
	}

} 

