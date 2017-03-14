#ifdef _DEBUG
#include <vld.h>
#include <vld_def.h>
#endif // _DEBUG

#include "src/graphics/window.h"
#include "src/graphics/engine/loader.h"
#include "src/graphics/engine/model_loader.h"
#include "src/graphics/renderer/water_renderer.h"
#include "src/graphics/renderer/multiple_renderer.h"
#include "src/graphics/gui/gui_renderer.h"
#include "src/graphics/water/water_frame_buffer.h"
#include "src/graphics/font/fontRenderer/font_renderer.h"
#include "src/utils/timer.h"
#include "src/utils/mouse_picker.h"
#include "src/utils/error_check.h"
#include "src/utils/mouse_picker.h"
#include "src/graphics/particle/particle_master.h"
#include "src/graphics/particle/particle_system.h"
#include "src/graphics/shadowMapping/shadow_mapping_master_renderer.h"


using namespace sloth;
using namespace graphics;
using namespace util;

void main()
{
	SlothWindow window("Sloth!", SCREEN_WIDTH, SCREEN_HEIGHT);
	Loader loader;
	MultipleRenderer renderer(loader);
	GuiRenderer guiRenderer(loader);
	TextMaster textMaster(loader);
	Camera camera;
	ParticleMaster particleMaster(loader,renderer.getProjectionMatrix());
	ShadowMappingMasterRenderer shadowMaster;


	// 地形
	auto background = loader.loadTexture("res/textures/grass.png");
	auto rTexture = loader.loadTexture("res/textures/mud.png");
	auto gTexture = loader.loadTexture("res/textures/grassFlowers.png");
	auto bTexture = loader.loadTexture("res/textures/path.png");
	auto blendmap = loader.loadTexture("res/textures/blendMap.png");
	std::vector<std::shared_ptr<Terrain>> terrains;
	std::shared_ptr<Terrain> terrain = 
		std::shared_ptr<Terrain>(new Terrain(0, 0, TerrainTexturePack(background, rTexture, gTexture, bTexture, blendmap), loader, "res/textures/heightmaps/heightmap.png"));
	terrains.push_back(terrain);

	// 模型
	ModelTexture pine_texture = loader.loadTexture("res/textures/pine.png", true);
	pine_texture.setTransparency(true);
	TexturedModel tree(ModelLoader::loadModel("res/models/pine.obj", loader), pine_texture);
	std::vector<std::shared_ptr<Entity>> entities;
	entities.push_back(
		std::shared_ptr<Entity>(new Entity(tree, glm::vec3(13.0f, terrain->getHeightOfTerrain(13.0f, 6.0f), 6.0f), 0, 0, 0, 0.3f)));
	entities.push_back(
		std::shared_ptr<Entity>(new Entity(tree, glm::vec3(30.0f, terrain->getHeightOfTerrain(30.0f, 4.0f), 4.0f), 0, 0, 0, 0.3f)));
	entities.push_back(
		std::shared_ptr<Entity>(new Entity(tree, glm::vec3(26.0f, terrain->getHeightOfTerrain(26.0f, 31.0f), 31.0f), 0, 0, 0, 0.3f)));

	// 法线贴图模型
	std::vector<std::shared_ptr<Entity>> normalMappingEntities;
	ModelTexture barrel_t(loader.loadTexture("res/textures/normalMapping/barrel.png"));
	RawModel barrel_raw = ModelLoader::loadModelNM("res/models/normalMapping/barrel.obj",loader);
	barrel_t.setNormalMap(loader.loadTexture("res/textures/normalMapping/barrelNormal.png"));

	normalMappingEntities.push_back(std::shared_ptr<Entity>(new
		Entity(
			TexturedModel(
				barrel_raw, barrel_t
			), glm::vec3(40.0f, 20.0f, 40.0f), 0, 0, 0, 1.0f)));

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
	WaterTile water(100.0f, 100.0f, 0.0f);
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
	//guis.push_back(GuiTexture(wfb.getReflectionTexture(), glm::vec2(-0.5f, 0.5f), glm::vec2(0.3f)));
	//guis.push_back(GuiTexture(wfb.getRefractionTexture(), glm::vec2(0.5f, 0.5f), glm::vec2(0.3f)));

	// 阴影贴图
	guis.push_back(GuiTexture(shadowMaster.getShadowMap(), glm::vec2(0.5f, 0.5f), glm::vec2(0.4f)));

	// 字体
	std::shared_ptr<FontType> font = std::shared_ptr<FontType>(new FontType(loader.loadTexture("res/consolas.png", true), "res/consolas.fnt"));
	std::shared_ptr<GUIText> text = std::shared_ptr<GUIText>(new GUIText("This is a test text! This is a test text! This is a test text! This is a test text!", 3, font, glm::vec2(0.0f, 1.0f), 1.0f, true));
	text->setColor(glm::vec3(1.0f));
	textMaster.loadText(text);

	// 粒子
	ParticleTexture particleTexture(loader.loadTexture("res/particleAtlas.png", true), 4);
	ParticleSystem particleSystem(particleTexture, 200.0f, 35.0f, 0.3f, 4.0f, 2.0f);
	particleSystem.randomizeRotation();
	particleSystem.setDirection(glm::vec3(0.0f, 1.0f, 0.0f), 90.0f);
	particleSystem.setLifeError(0.6f);
	particleSystem.setSpeedError(0.4f);
	particleSystem.setScaleError(0.8f);

	MousePicker mousePicker(camera, renderer.getProjectionMatrix(), *terrain);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	while (window.isRunning())
	{
		window.clear();
#pragma region USER

		particleSystem.generateParticles(glm::vec3(100.0f, 30.0f, 100.0f), particleMaster);

		mousePicker.update();
		particleMaster.update(camera);

		shadowMaster.renderScene(entities, lights[0], camera);

		glEnable(GL_CLIP_DISTANCE0);

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

		particleMaster.renderParticles(camera);

		guiRenderer.render(guis);
		//textMaster.render();
		glCheckError();
#pragma endregion
		Timer::calculateFPS();
		camera.process(&window);
		window.update();
		if (Timer::frameCounter % 60 == 0)
			printf("%d fps\n", Timer::FPS);
	}
	glfwTerminate();
}