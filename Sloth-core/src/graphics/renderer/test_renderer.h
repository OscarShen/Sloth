/************************************************************************ 
 * @project 	:  $rootnamespace$
 * @class   	:  $safeitemrootname$
 * @version 	:  v1.0.0
 * @description :  
 * @author		:  $username$
 * @creat 		:  $time$
 * @revise 		:  $time$
************************************************************************ 
 * Copyright @ OscarShen 2017. All rights reserved. 
************************************************************************/  
#pragma once
#ifndef SLOTH_TEST_RENDERER_H_
#define SLOTH_TEST_RENDERER_H_

#include "../shader/test_shader.h"
#include "../entities/entity.h"
#include "../../utils/maths.h"
namespace sloth { namespace graphics {

	class TestRenderer
	{
	public:
		TestRenderer() {}
		TestRenderer(glm::mat4 &projection);

		void render(Entity &entity);

	private:
		void prepareTexturedModel(const TexturedModel &model) const;

		void prepareInstance(Entity &entity);

		void unbindTexturedModel();
	};

} }

#endif // !SLOTH_TEST_RENDERER_H_
