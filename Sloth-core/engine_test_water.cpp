
#include "src/graphics/window.h"
#include "src/graphics/engine/loader.h"
#include "src/graphics/model/model_loader.h"
#include "src/utils/timer.h"
#include "src/utils/mouse_picker.h"
#include "src/utils/error_check.h"
#include "src/graphics/renderer/water_renderer.h"
#include "src/graphics/renderer/multiple_renderer.h"

using namespace sloth;
using namespace graphics;
using namespace util;

void main()
{
	SlothWindow window("Sloth!", SCREEN_WIDTH, SCREEN_HEIGHT);
	Loader loader;
	MultipleRenderer renderer(loader);
	WaterRenderer waterRenderer(loader, renderer.getProjectionMatrix());
	Camera camera;

	std::vector<Light> lights;
	lights.push_back(Light(glm::vec3(10000.0f, 10000.0f, -10000.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 0.0f, 0.0f)));

	auto background = loader.loadTexture("res/textures/grass.png");
	auto rTexture = loader.loadTexture("res/textures/mud.png");
	auto gTexture = loader.loadTexture("res/textures/grassFlowers.png");
	auto bTexture = loader.loadTexture("res/textures/path.png");
	auto blendmap = loader.loadTexture("res/textures/blendMap.png");

	Terrain *terrain = new Terrain(0, 0, TerrainTexturePack(background, rTexture, gTexture, bTexture, blendmap), loader, "res/textures/heightmaps/heightmap.png");

	std::vector<Terrain*> terrains;
	terrains.push_back(terrain);

	std::vector<std::string> cubeMapPath = { "res/right.png","res/left.png", "res/top.png", "res/bottom.png", "res/back.png", "res/front.png" };
	CubeMapTexture cubemap(loader.loadCubeMap(cubeMapPath));

	std::vector<WaterTile> waters;
	waters.push_back(WaterTile(20.0f, 20.0f, 0.0f));

	TexturedModel tree(ModelLoader::loadModel("res/models/pine.obj", loader), loader.loadTexture("res/textures/pine.png", true));

	std::vector<Entity> entities;
	entities.push_back(Entity(tree, glm::vec3(13.0f, terrain->getHeightOfTerrain(13.0f, 6.0f), 6.0f), 0, 0, 0, 0.3f));
	entities.push_back(Entity(tree, glm::vec3(30.0f, terrain->getHeightOfTerrain(30.0f, 4.0f), 4.0f), 0, 0, 0, 0.3f));
	entities.push_back(Entity(tree, glm::vec3(26.0f, terrain->getHeightOfTerrain(26.0f, 31.0f), 31.0f), 0, 0, 0, 0.3f));

	glEnable(GL_DEPTH_TEST);
	StaticShader *ss = StaticShader::inst();

	while (window.isRunning())
	{
		window.clear();
#pragma region USER
		renderer.renderScene(entities, terrains, lights, camera, cubemap);
		waterRenderer.render(waters, camera);
#pragma endregion
		Timer::calculateFPS();
		camera.process(&window);
		window.update();
		//if (Timer::frameCounter % 60 == 0)
		//	printf("%d fps\n", Timer::FPS);
	}
}