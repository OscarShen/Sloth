#include "sprite.h"

sloth::graphics::Sprite::Sprite(float x, float y, float width, float height, glm::vec4 & color)
	:Renderable2D(glm::vec3(x, y, 0.0f), glm::vec2(width, height), color)
{
}
