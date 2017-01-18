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
#include "src/graphics/renderer/terrain_renderer.h"
#include "src/graphics/renderer/multiple_renderer.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
using namespace sloth;
using namespace graphics;
using namespace util;

enum Texture
{
	WOOD = 1,
	WHITE = 0,
	GRASS = 2
};

enum Shader
{
	BASIC_SHADER = 1,
	DEPTH_SHADER = 2
};

int main()
{
	SlothWindow window("Sloth!", SCREEN_WIDTH, SCREEN_HEIGHT);
	Camera camera;
	Loader loader;
	Timer timer;
	TextureManager2D * tm = TextureManager2D::inst();
	TerrainShader *terrainShader = TerrainShader::inst();
	MultipleRenderer renderer;

	tm->loadTexture(Texture::GRASS, "res/grass.png");
	tm->loadTexture(Texture::WHITE, "res/white.jpg");

	RawModel raw_dragon = ModelLoader::loadModel("res/dragon.obj", loader);
	Entity dragon(TexturedModel(raw_dragon, Texture::WHITE), glm::vec3(0.0f),
		0.0f, 0.0f, 0.0f, 1.0f);

	//std::vector<Terrain> terrains;
	//terrains.push_back(Terrain(0, 0, Texture::GRASS, loader));
	Terrain grassLand(0, 0, Texture::GRASS, loader);

	//std::vector<Light> lights;
	//lights.push_back(Light(glm::vec3(0.0f, 10000.0f, 0.0f), glm::vec3(1.0f)));
	//terrainShader->loadLights(lights);

	Light sun(glm::vec3(0.0f, 10000.0f, 0.0f), glm::vec3(1.0f));

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	while (window.isRunning())
	{
		window.clear();
#pragma region USER
		renderer.submitEntity(dragon);
		renderer.submitTerrain(grassLand);
		renderer.render(sun, camera);
#pragma endregion
		timer.calculateFPS();
		graphics::Input::process(&window, &camera, static_cast<float>(timer.getDeltaFrameTime()));
		window.update();
		if (timer.getFramerCounter() % 2000 == 0)
			printf("%d fps\n", timer.getFPS());
	}
}
