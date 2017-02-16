
#include "src/graphics/window.h"
#include "src/graphics/engine/loader.h"
#include "src/graphics/model/model_loader.h"
#include "src/utils/timer.h"
#include "src/utils/mouse_picker.h"
#include "src/utils/error_check.h"
#include "src/graphics/renderer/water_renderer.h"
#include "src/graphics/renderer/multiple_renderer.h"
#include "src/graphics/gui/gui_renderer.h"
#include "src/graphics/water/water_frame_buffer.h"

using namespace sloth;
using namespace graphics;
using namespace util;

GLuint generateAttachmentTexture(GLboolean depth, GLboolean stencil)
{
	// What enum to use?
	GLenum attachment_type;
	if (!depth && !stencil)
		attachment_type = GL_RGB;
	else if (depth && !stencil)
		attachment_type = GL_DEPTH_COMPONENT;
	else if (!depth && stencil)
		attachment_type = GL_STENCIL_INDEX;

	//Generate texture ID and load texture data 
	GLuint textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	if (!depth && !stencil)
		glTexImage2D(GL_TEXTURE_2D, 0, attachment_type, SCREEN_WIDTH, SCREEN_HEIGHT, 0, attachment_type, GL_UNSIGNED_BYTE, NULL);
	else // Using both a stencil and depth test, needs special format arguments
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, SCREEN_WIDTH, SCREEN_HEIGHT, 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);

	return textureID;
}

void main()
{
	SlothWindow window("Sloth!", SCREEN_WIDTH, SCREEN_HEIGHT);
	Loader loader;
	MultipleRenderer renderer(loader);
	WaterRenderer waterRenderer(loader, renderer.getProjectionMatrix());
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
	TexturedModel tree(ModelLoader::loadModel("res/models/pine.obj", loader), loader.loadTexture("res/textures/pine.png", true));
	std::vector<Entity> entities;
	entities.push_back(Entity(tree, glm::vec3(13.0f, terrain->getHeightOfTerrain(13.0f, 6.0f), 6.0f), 0, 0, 0, 0.3f));
	entities.push_back(Entity(tree, glm::vec3(30.0f, terrain->getHeightOfTerrain(30.0f, 4.0f), 4.0f), 0, 0, 0, 0.3f));
	entities.push_back(Entity(tree, glm::vec3(26.0f, terrain->getHeightOfTerrain(26.0f, 31.0f), 31.0f), 0, 0, 0, 0.3f));

	// 天空盒
	std::vector<std::string> cubeMapPath = { "res/right.png","res/left.png", "res/top.png", "res/bottom.png", "res/back.png", "res/front.png" };
	CubeMapTexture cubemap(loader.loadCubeMap(cubeMapPath));

	// 水面
	std::vector<WaterTile> waters;
	waters.push_back(WaterTile(20.0f, 20.0f, 0.0f));

	// 灯光
	std::vector<Light> lights;
	lights.push_back(Light(glm::vec3(10000.0f, 10000.0f, -10000.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 0.0f, 0.0f)));

	// 离线渲染
	//WaterFrameBuffer wfb;
	FrameBuffer fbo;
	fbo.addColorAttachment(0, 800, 600);
	fbo.addDepthRenderBufferAttachment(800, 600);

	// GUI
	std::vector<GuiTexture> guis;
	guis.push_back(GuiTexture(loader.loadTexture("res/health.png", true), glm::vec2(-0.5f), glm::vec2(0.3f)));
	//guis.push_back(GuiTexture(wfb.getReflectionTexture(), glm::vec2(-0.5f, 0.5f), glm::vec2(0.5f)));
	guis.push_back(GuiTexture(fbo.getColorTexture(0), glm::vec2(-0.5f, 0.5f), glm::vec2(0.3f)));


	//GLuint framebuffer;
	//glGenFramebuffers(1, &framebuffer);
	//glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
	//// Create a color attachment texture
	//GLuint textureColorbuffer = generateAttachmentTexture(false, false);
	//glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureColorbuffer, 0);
	//// Create a renderbuffer object for depth and stencil attachment (we won't be sampling these)
	//GLuint rbo;
	//glGenRenderbuffers(1, &rbo);
	//glBindRenderbuffer(GL_RENDERBUFFER, rbo);
	//glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, SCREEN_WIDTH, SCREEN_HEIGHT); // Use a single renderbuffer object for both a depth AND stencil buffer.
	//glBindRenderbuffer(GL_RENDERBUFFER, 0);
	//glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo); // Now actually attach it
	//																							  // Now that we actually created the framebuffer and added all attachments we want to check if it is actually complete now
	//if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	//	std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
	//glBindFramebuffer(GL_FRAMEBUFFER, 0);

	//guis.push_back(GuiTexture(textureColorbuffer, glm::vec2(-0.5f, 0.5f), glm::vec2(0.5f)));

	glEnable(GL_DEPTH_TEST);
	while (window.isRunning())
	{
		window.clear();
#pragma region USER
		//wfb.bindReflectionFrameBuffer();
		fbo.bind(800,600);
		renderer.renderScene(entities, terrains, lights, camera, cubemap);
		waterRenderer.render(waters, camera);
		guiRenderer.render(guis);
		fbo.unbind();
		//wfb.unbind();

		renderer.renderScene(entities, terrains, lights, camera, cubemap);
		waterRenderer.render(waters, camera);
		guiRenderer.render(guis);
		glCheckError();
#pragma endregion
		Timer::calculateFPS();
		camera.process(&window);
		window.update();
		//if (Timer::frameCounter % 60 == 0)
		//	printf("%d fps\n", Timer::FPS);
	}
}