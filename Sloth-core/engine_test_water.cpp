
#include "src/graphics/window.h"
#include "src/graphics/engine/loader.h"
#include "src/graphics/engine/model_loader.h"
#include "src/graphics/renderer/water_renderer.h"
#include "src/graphics/renderer/multiple_renderer.h"
#include "src/graphics/gui/gui_renderer.h"
#include "src/graphics/water/water_frame_buffer.h"
#include "src/utils/timer.h"
#include "src/utils/mouse_picker.h"
#include "src/utils/error_check.h"
#include "src/utils/mouse_picker.h"

using namespace sloth;
using namespace graphics;
using namespace util;

void main()
{
	SlothWindow window("Sloth!", SCREEN_WIDTH, SCREEN_HEIGHT);
	Loader loader;
	MultipleRenderer renderer(loader);
	GuiRenderer guiRenderer(loader);
	Camera camera;

	// 地形
	auto background = loader.loadTexture("res/textures/grass.png");
	auto rTexture = loader.loadTexture("res/textures/mud.png");
	auto gTexture = loader.loadTexture("res/textures/grassFlowers.png");
	auto bTexture = loader.loadTexture("res/textures/path.png");
	auto blendmap = loader.loadTexture("res/textures/blendMap.png");
	Terrain *terrain = new Terrain(0, 0, TerrainTexturePack(background, rTexture, gTexture, bTexture, blendmap), loader, "res/textures/heightmaps/heightmap.png");
	std::vector<Terrain*> terrains;
	terrains.push_back(terrain);

	// 模型
	ModelTexture pine_texture = loader.loadTexture("res/textures/pine.png", true);
	pine_texture.setTransparency(true);
	TexturedModel tree(ModelLoader::loadModel("res/models/pine.obj", loader), pine_texture);
	std::vector<Entity> entities;
	entities.push_back(Entity(tree, glm::vec3(13.0f, terrain->getHeightOfTerrain(13.0f, 6.0f), 6.0f), 0, 0, 0, 0.3f));
	entities.push_back(Entity(tree, glm::vec3(30.0f, terrain->getHeightOfTerrain(30.0f, 4.0f), 4.0f), 0, 0, 0, 0.3f));
	entities.push_back(Entity(tree, glm::vec3(26.0f, terrain->getHeightOfTerrain(26.0f, 31.0f), 31.0f), 0, 0, 0, 0.3f));

	// 法线贴图模型
	std::vector<Entity> normalMappingEntities;
	ModelTexture barrel_t(loader.loadTexture("res/textures/normalMapping/barrel.png"));
	RawModel barrel_raw = ModelLoader::loadModelNM("res/models/normalMapping/barrel.obj",loader);
	barrel_t.setNormalMap(loader.loadTexture("res/textures/normalMapping/barrelNormal.png"));

	normalMappingEntities.push_back(
		Entity(
			TexturedModel(
				barrel_raw, barrel_t
			), glm::vec3(40.0f, 20.0f, 40.0f), 0, 0, 0, 1.0f));

	// 天空盒
	std::vector<std::string> cubeMapPath = { 
		"res/textures/skybox/right.png",
		"res/textures/skybox/left.png", 
		"res/textures/skybox/top.png", 
		"res/textures/skybox/bottom.png", 
		"res/textures/skybox/back.png", 
		"res/textures/skybox/front.png" };
	CubeMapTexture cubemap(loader.loadCubeMap(cubeMapPath));
	// 水面
	std::vector<WaterTile> waters;
	WaterTile water(40.0f, 40.0f, 0.0f);
	waters.push_back(water);

	// 灯光
	Light sun(glm::vec3(4500.0f, 8000.0f, -3400.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	std::vector<Light> lights;
	lights.push_back(sun);

	// 离线渲染
	WaterFrameBuffer wfb;
	WaterRenderer waterRenderer(loader, renderer.getProjectionMatrix(), wfb);

	// GUI
	std::vector<GuiTexture> guis;
	guis.push_back(GuiTexture(loader.loadTexture("res/health.png", true), glm::vec2(-0.5f), glm::vec2(0.3f)));
	guis.push_back(GuiTexture(wfb.getReflectionTexture(), glm::vec2(-0.5f, 0.5f), glm::vec2(0.3f)));
	guis.push_back(GuiTexture(wfb.getRefractionTexture(), glm::vec2(0.5f, 0.5f), glm::vec2(0.3f)));

	MousePicker mousePicker(camera, renderer.getProjectionMatrix(), *terrain);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	while (window.isRunning())
	{
		window.clear();
#pragma region USER

		glEnable(GL_CLIP_DISTANCE0);

		mousePicker.update();

		//std::cout << mousePicker.getCurrentRay().x << " " << mousePicker.getCurrentRay().y << " " << mousePicker.getCurrentRay().z << std::endl;

		wfb.bindReflectionFrameBuffer();
		float distance = (camera.getPosition().y - water.getHeight()) * 2;
		auto position = camera.getPosition();
		position.y -= distance;
		camera.setPosition(position);
		camera.invertPitch();
		renderer.renderScene(entities, normalMappingEntities, terrains, lights, camera, cubemap, glm::vec4(0.0f, 1.0f, 0.0f, -water.getHeight() + 1.0f));
		camera.invertPitch();
		position.y += distance;
		camera.setPosition(position);

		wfb.bindRefractionFrameBuffer();
		renderer.renderScene(entities, normalMappingEntities, terrains, lights, camera, cubemap, glm::vec4(0.0f, -1.0f, 0.0f, water.getHeight()));
		wfb.unbind();

		glDisable(GL_CLIP_DISTANCE0);
		renderer.renderScene(entities, normalMappingEntities, terrains, lights, camera, cubemap, glm::vec4(0.0f, 1.0f, 0.0f, 0.0f));
		waterRenderer.render(waters, camera, sun);

		slothCheckError(__FILE__, __LINE__);
#pragma endregion
		Timer::calculateFPS();
		camera.process(&window);
		window.update();
		if (Timer::frameCounter % 60 == 0)
			printf("%d fps\n", Timer::FPS);
	}
}