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
#include "src/graphics/terrain/multi_terrain.h"
#include "src/graphics/entities/player.h"

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
	TREE = 3,
	FERN = 4,
	GRASS_TEXTURE = 5,

	BACKGROUND = 6,
	RTEXTURE = 7,
	GTEXTURE = 8,
	BTEXTURE = 9,
	BLENDMAP = 10,

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
	TextureManager2D * tm = TextureManager2D::inst();
	TerrainShader *terrainShader = TerrainShader::inst();
	MultipleRenderer renderer;

	tm->loadTexture(Texture::WHITE, "res/white.png");
	tm->loadTexture(Texture::TREE, "res/tree.png");
	tm->loadTexture(Texture::FERN, "res/fern.png", true);
	tm->getTexture(Texture::FERN)->setTransparency(true);
	tm->loadTexture(Texture::GRASS_TEXTURE, "res/grassTexture.png", true);
	tm->getTexture(Texture::GRASS_TEXTURE)->setUseFakeLighting(true);
	tm->getTexture(Texture::GRASS_TEXTURE)->setReflectivity(false);

	tm->loadTexture(Texture::BACKGROUND, "res/grass.png");
	tm->loadTexture(Texture::RTEXTURE, "res/rocks.png");
	tm->loadTexture(Texture::GTEXTURE, "res/grassFlowers.png");
	tm->loadTexture(Texture::BTEXTURE, "res/path.png");
	tm->loadTexture(Texture::BLENDMAP, "res/blendMap.png");

	Terrain terrain(0, 0, MultiTerrain(Texture::BACKGROUND, Texture::RTEXTURE, Texture::GTEXTURE, Texture::BTEXTURE, Texture::BLENDMAP), loader);
	TexturedModel tree(ModelLoader::loadModel("res/tree.obj", loader), Texture::TREE);
	TexturedModel fern(ModelLoader::loadModel("res/fern.obj", loader), Texture::FERN);
	TexturedModel grassModel(ModelLoader::loadModel("res/grassModel.obj", loader), Texture::GRASS_TEXTURE);
	TexturedModel dragon(ModelLoader::loadModel("res/bunny.obj", loader), Texture::WHITE);

	std::vector<Entity> entities;
	float p = 1.0f / 800.0f;
	for (int i = 0; i < 500; ++i) {
		int r1 = rand() % 800, r2 = rand() % 800;
		entities.push_back(Entity(tree, glm::vec3(r1, 0, r2), 0, 0, 0, 3));
	}
	for (int i = 0; i < 200; ++i) {
		int r1 = rand() % 800, r2 = rand() % 800, r3 = rand() % 800, r4 = rand() % 800;
		entities.push_back(Entity(fern, glm::vec3(r1, 0, r2), 0, 0, 0, 1));
		entities.push_back(Entity(grassModel, glm::vec3(r3, 0, r4), 0, 0, 0, 2));
	}

	Light sun(glm::vec3(10000.0f, 10000.0f, 10000.0f), glm::vec3(1.2f));
	Player player(dragon, glm::vec3(0.0f), 0.0f, 0.0f, 0.0f, 1.0f);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	while (window.isRunning())
	{
		window.clear();
#pragma region USER
		player.move();
		renderer.submitEntity(player);
		renderer.submitTerrain(terrain);
		for (size_t i = 0; i < entities.size(); ++i) {
			renderer.submitEntity(entities[i]);
		}
		renderer.render(sun, camera);
#pragma endregion
		Timer::calculateFPS();
		graphics::Input::process(&window, &camera, static_cast<float>(Timer::deltaFrameTime));
		window.update();
		if (Timer::frameCounter % 60 == 0)
			printf("%d fps\n", Timer::FPS);
	}
}
