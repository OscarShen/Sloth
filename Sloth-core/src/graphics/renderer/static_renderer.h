#pragma once
#ifndef SLOTH_STATIC_RENDERER_H_
#define SLOTH_STATIC_RENDERER_H_

#include <GL/glew.h>
#include <map>
#include <vector>
#include "../shader/static_shader.h"
#include "../model/textured_model.hpp"
#include "../entities/entity.h"
#include "../texture/texture_manager_2d.h"
#include "../../utils/maths.h"
namespace sloth { namespace graphics {

	class StaticRenderer
	{
	private:
		StaticShader *m_Shader;

	public:
		StaticRenderer(StaticShader *shader);

		void render(Entity &entity);
		void render(std::map<TexturedModel, std::vector<Entity>> &entities);

	private:
		void prepareTexturedModel(const TexturedModel &model);

		void prepareInstance(Entity &entity);
	};

} }



#endif // !SLOTH_STATIC_RENDERER_H_
