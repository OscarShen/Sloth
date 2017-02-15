#pragma once
#ifndef SLOTH_STATIC_RENDERER_H_
#define SLOTH_STATIC_RENDERER_H_

#include <GL/glew.h>
#include <map>
#include <vector>
#include "../shader/static_shader.h"
#include "../model/textured_model.hpp"
#include "../entities/entity.h"
#include "../../utils/maths.h"
#include "../setup/global_function.h"
namespace sloth { namespace graphics {

	class StaticRenderer
	{
	public:
		StaticRenderer() {}
		StaticRenderer(glm::mat4 &projection);

		void render(Entity &entity);
		void render(std::map<TexturedModel, std::vector<Entity>> &entities);

	private:
		void prepareTexturedModel(const TexturedModel &model) const;

		void prepareInstance(Entity &entity);

		void unbindTexturedModel();
	};

} }



#endif // !SLOTH_STATIC_RENDERER_H_
