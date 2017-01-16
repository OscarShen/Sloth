#include "entity.h"

namespace sloth { namespace graphics {
	Entity::Entity(const TexturedModel & model, const glm::vec3 & position, const float rotX, const float rotY, const float rotZ, float scale)
		:m_Model(model), m_Position(position), m_RotX(rotX), m_RotY(rotY), m_RotZ(rotZ), m_Scale(scale) {}

} }
