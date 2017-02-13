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
#include "src/graphics/camera/camera_3rd.h"
#include "src/graphics/gui/gui_renderer.h"
#include "src/graphics/gui/gui_shader.h"
#include "src/graphics/gui/gui_texture.hpp"
#include "src/utils/mouse_picker.h"

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
	PLAYER = 11,

	GUI_HEALTH = 30,

	CUBE_MAP_DAY = 1000
};

int main()
{
	SlothWindow window("Sloth!", SCREEN_WIDTH, SCREEN_HEIGHT);
	Loader loader;
	TextureManager2D * tm = TextureManager2D::inst();
	MultipleRenderer renderer(loader);

	tm->loadTexture(Texture::WHITE, "res/white.png");
	tm->loadTexture(Texture::TREE, "res/tree.png");
	tm->loadTexture(Texture::FERN, "res/fern.png", true);
	tm->getTexture(Texture::FERN)->setTransparency(true);
	tm->getTexture(Texture::FERN)->setNumberOfRows(2);

	tm->loadTexture(Texture::GRASS_TEXTURE, "res/grassTexture.png", true);
	tm->getTexture(Texture::GRASS_TEXTURE)->setUseFakeLighting(true);
	tm->getTexture(Texture::GRASS_TEXTURE)->setReflectivity(false);
	tm->loadTexture(Texture::PLAYER, "res/playerTexture.png");

	tm->loadTexture(Texture::BACKGROUND, "res/grass.png");
	tm->loadTexture(Texture::RTEXTURE, "res/mud.png");
	tm->loadTexture(Texture::GTEXTURE, "res/grassFlowers.png");
	tm->loadTexture(Texture::BTEXTURE, "res/path.png");
	tm->loadTexture(Texture::BLENDMAP, "res/blendMap.png");

	std::vector<std::string> cubeMapPath = { "res/right.png","res/left.png", "res/top.png", "res/bottom.png", "res/back.png", "res/front.png" };
	tm->loadCubeMap(Texture::CUBE_MAP_DAY, cubeMapPath);

	Terrain terrain(0, 0, MultiTerrain(Texture::BACKGROUND, Texture::RTEXTURE, Texture::GTEXTURE, Texture::BTEXTURE, Texture::BLENDMAP), loader, "res/heightmap2.jpg");
	TexturedModel tree(ModelLoader::loadModel("res/tree.obj", loader), Texture::TREE);
	TexturedModel fern(ModelLoader::loadModel("res/fern.obj", loader), Texture::FERN);
	TexturedModel grassModel(ModelLoader::loadModel("res/grassModel.obj", loader), Texture::GRASS_TEXTURE);
	TexturedModel person(ModelLoader::loadModel("res/person.obj", loader), Texture::PLAYER);

	std::vector<Entity> entities;
	float p = 1.0f / 800.0f;
	for (int i = 0; i < 100; ++i) {
		int r1 = rand() % 800, r2 = rand() % 800;
		entities.push_back(Entity(tree, glm::vec3(r1, terrain.getHeightOfTerrain((float) r1,(float) r2), r2), 0, 0, 0, 10));
	}
	for (int i = 0; i < 200; ++i) {
		int r1 = rand() % 800, r2 = rand() % 800, r3 = rand() % 800, r4 = rand() % 800, r5 = rand() % 4;
		entities.push_back(Entity(fern, glm::vec3(r1, terrain.getHeightOfTerrain((float) r1, (float) r2), r2), r5, 0, 0, 0, 1));
		entities.push_back(Entity(grassModel, glm::vec3(r3, terrain.getHeightOfTerrain((float) r3, (float) r4), r4), 0, 0, 0, 2));
	}

	auto guiShader = GuiShader::inst();
	GuiRenderer guiRenderer(loader);
	tm->loadTexture(Texture::GUI_HEALTH, "res/health.png", true);
	std::vector<GuiTexture> guiTextures;
	guiTextures.push_back(GuiTexture(Texture::GUI_HEALTH, glm::vec2(-0.5f, -0.7f), glm::vec2(0.3f)));

	//Light sun(glm::vec3(0.0f, 10000.0f, 0.0f), glm::vec3(1.2f));
	std::vector<Light> lights;
	lights.push_back(Light(glm::vec3(400.0f, 10.0f, 400.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f,0.01f,0.002f)));
	//lights.push_back(Light(glm::vec3(000.0f, 100.0f, -100.0f), glm::vec3(0.0f, 1.0f, 0.0f),glm::vec3(1.0f,0.2f,0.07f)));
	//lights.push_back(Light(glm::vec3(100.0f, 100.0f, 000.0f), glm::vec3(0.0f, 0.0f, 1.0f)));
	Player player(person, glm::vec3(400.0f, 0.0f, 400.0f), 0.0f, 0.0f, 0.0f, 1.0f);

	Camera3rd camera(player);
	//Camera camera;

	MousePicker picker(camera, renderer.getProjectionMatrix(),terrain);
	Entity pickerTree(tree, glm::vec3(400.0f, terrain.getHeightOfTerrain(400.0f, 400.0f), 400.0f), 0, 0, 0, 10);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	while (window.isRunning())
	{
		window.clear();
#pragma region USER


		picker.update();
		glm::vec3 terrainPoint = picker.getCurrentTerrainPosition();
		pickerTree.setPosition(terrainPoint);

		player.move(terrain);
		renderer.submitEntity(player);
		renderer.submitEntity(pickerTree);
		renderer.submitTerrain(terrain);
		for (size_t i = 0; i < entities.size(); ++i) {
			renderer.submitEntity(entities[i]);
		}
		renderer.render(lights, camera, Texture::CUBE_MAP_DAY);
		guiRenderer.render(guiTextures);
#pragma endregion
		Timer::calculateFPS();
		camera.process(&window);
		window.update();
		if (Timer::frameCounter % 60 == 0)
			printf("%d fps\n", Timer::FPS);
	}
}
