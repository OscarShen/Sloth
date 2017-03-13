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
#include <memory>
#include <unordered_map>
namespace sloth { namespace graphics {

	class StaticRenderer
	{
	public:
		typedef std::unordered_map<TexturedModel, std::list<std::shared_ptr<Entity>>> MapedEntities;
		StaticRenderer() {}
		StaticRenderer(glm::mat4 &projection);

		void render(Entity &entity);
		void render(MapedEntities &entities);

	private:
		void prepareTexturedModel(const TexturedModel &model) const;

		void prepareInstance(Entity &entity);

		void unbindTexturedModel();
	};

} }



#endif // !SLOTH_STATIC_RENDERER_H_
