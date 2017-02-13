
#include "src/graphics/window.h"
#include "src/graphics/engine/loader.h"
#include "src/graphics/texture/texture_manager_2d.h"
#include "src/graphics/renderer/multiple_renderer.h"
#include "src/graphics/renderer/water_renderer.h"
#include "src/graphics/model/model_loader.h"
#include "src/utils/timer.h"
#include "src/utils/mouse_picker.h"
#include "src/utils/error_check.h"

using namespace sloth;
using namespace graphics;
using namespace util;

enum Texture
{
	PINE = 1,


	BACKGROUND = 100,
	RTEXTURE = 101,
	GTEXTURE = 102,
	BTEXTURE = 103,
	BLENDMAP = 104,

	CUBE_MAP_DAY = 1000
};

void main()
{
	SlothWindow window("Sloth!", SCREEN_WIDTH, SCREEN_HEIGHT);
	Loader loader;
	TextureManager2D * tm = TextureManager2D::inst();
	MultipleRenderer renderer(loader);
	WaterRenderer waterRenderer(loader, renderer.getProjectionMatrix());

	tm->loadTexture(Texture::BACKGROUND, "res/textures/grass.png");
	tm->loadTexture(Texture::RTEXTURE, "res/textures/mud.png");
	tm->loadTexture(Texture::GTEXTURE, "res/textures/grassFlowers.png");
	tm->loadTexture(Texture::BTEXTURE, "res/textures/path.png");
	tm->loadTexture(Texture::BLENDMAP, "res/textures/blendMap.png");
	tm->loadTexture(Texture::PINE, "res/textures/pine.png", true);
	tm->getTexture(Texture::PINE)->setReflectivity(0.0f);

	std::vector<std::string> cubeMapPath = { "res/right.png","res/left.png", "res/top.png", "res/bottom.png", "res/back.png", "res/front.png" };
	tm->loadCubeMap(Texture::CUBE_MAP_DAY, cubeMapPath);

	TexturedModel tree(ModelLoader::loadModel("res/models/pine.obj", loader), Texture::PINE);

	std::vector<Light> lights;
	lights.push_back(Light(glm::vec3(2000.0, 10000.0f, 400.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 0.0f, 0.0f)));

	Camera camera;

	//Terrain terrain(0, 0, MultiTerrain(Texture::BACKGROUND, Texture::RTEXTURE, Texture::GTEXTURE, Texture::BTEXTURE, Texture::BLENDMAP), loader, "res/textures/heightmaps/heightmap.png");
	Terrain *terrain = new Terrain(0, 0, MultiTerrain(Texture::BACKGROUND, Texture::RTEXTURE, Texture::GTEXTURE, Texture::BTEXTURE, Texture::BLENDMAP), loader, "res/textures/heightmaps/heightmap.png");

	std::vector<Terrain*> terrains;
	terrains.push_back(terrain);

	std::vector<Entity> entities;
	entities.push_back(Entity(tree, glm::vec3(13.0f, terrain->getHeightOfTerrain(13.0f, 6.0f), 6.0f), 0, 0, 0, 0.3f));
	entities.push_back(Entity(tree, glm::vec3(30.0f, terrain->getHeightOfTerrain(30.0f, 4.0f), 4.0f), 0, 0, 0, 0.3f));
	entities.push_back(Entity(tree, glm::vec3(26.0f, terrain->getHeightOfTerrain(26.0f, 31.0f), 31.0f), 0, 0, 0, 0.3f));

	std::vector<WaterTile> waters;
	waters.push_back(WaterTile(20.0f, 20.0f, 0.0f));

	glEnable(GL_DEPTH_TEST);

	while (window.isRunning())
	{
		window.clear();
#pragma region USER
		renderer.renderScene(entities, terrains, lights, camera, CUBE_MAP_DAY);
		waterRenderer.render(waters, camera);
		glCheckError();
#pragma endregion
		Timer::calculateFPS();
		camera.process(&window);
		window.update();
		if (Timer::frameCounter % 60 == 0)
			printf("%d fps\n", Timer::FPS);
	}
}