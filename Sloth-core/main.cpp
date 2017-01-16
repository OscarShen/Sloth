#include "src/graphics/window.h"
#include "src/graphics/buffers/buffer.h"
#include "src/graphics/buffers/vertex_array.h"
#include "src/graphics/buffers/index_buffer.h"
#include "src/utils/error_check.h"
#include "src/utils/timer.h"
#include "src/graphics/texture/texture_2d.h"
#include "src/graphics/texture/texture_manager_2d.h"
#include "src/graphics/info/info.h"
#include "src/graphics/shader/static_shader.h"
#include "src/graphics/engine/loader.h"
#include "src/graphics/model/model_loader.h"
#include "src/graphics/model/textured_model.hpp"
#include "src/graphics/entities/entity.h"
#include "src/graphics/renderer/static_renderer.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
using namespace sloth;
using namespace graphics;
using namespace util;

enum Texture
{
	WOOD = 1,
	WHITE = 0
};

enum Shader
{
	BASIC_SHADER = 1,
	DEPTH_SHADER = 2
};

int main()
{
	SlothWindow window("Sloth!", 800, 600);
	Camera camera;

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	TextureManager2D * tm = TextureManager2D::inst();
	StaticShader *shader = StaticShader::inst();
	Loader loader;
	ModelData *modeldata = ModelLoader::loadModel("res/dragon.obj");
	tm->loadTexture(Texture::WHITE, "res/white.jpg");
	RawModel raw_model = loader.loadToVAO(modeldata);
	TexturedModel textured_model(raw_model, Texture::WHITE);
	Entity *entity = new Entity(textured_model, glm::vec3(0.0f), 0.0f, 0.0f, 0.0f, 1.0f);
	StaticRenderer renderer(shader);
	
	ModelLoader::releaseModelData(modeldata);
	shader->laodProjectionMatrix(glm::perspective(45.0f, 800.0f / 600.0f, 0.1f, 100.0f));
	std::vector<Light> lights;
	lights.push_back(Light(glm::vec3(0.0f, 0.0f, 10.0f), glm::vec3(1.0f)));
	shader->loadLights(lights);

	glEnable(GL_DEPTH_TEST);
	Timer timer;
	while (!window.closed())
	{
		window.clear();
#pragma region USER
		shader->use();
		shader->loadViewMatrix(camera);

		renderer.render(*entity);

#pragma endregion
		window.update();
		timer.calculateFPS();
		graphics::Input::process(&window, &camera, static_cast<float>(timer.getDeltaFrameTime()));
		if (timer.getFramerCounter() % 2000 == 0)
			printf("%d fps\n", timer.getFPS());
	}
}
