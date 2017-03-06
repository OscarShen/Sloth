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
#include "src/graphics/renderer/test_renderer.h"


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

	TestRenderer testRenderer(renderer.getProjectionMatrix());

	std::vector<glm::vec3> positions{
		glm::vec3(-100.0f,-100.0f,-100.0f),
		glm::vec3(100.0f,-100.0f,-100.0f),
		glm::vec3(-100.0f,100.0f,-100.0f),

		glm::vec3(-100.0f,100.0f,-100.0f),
		glm::vec3(100.0f,-100.0f,-100.0f),
		glm::vec3(100.0f,100.0f,-100.0f)
	};
	std::vector<glm::vec2> texCoords{
		glm::vec2(0.0f,1.0f),
		glm::vec2(1.0f,1.0f),
		glm::vec2(0.0f,0.0f),

		glm::vec2(0.0f,0.0f),
		glm::vec2(1.0f,1.0f),
		glm::vec2(1.0f,0.0f)
	};

	RawModel rawModel = loader.loadToVAO(positions, texCoords);
	ModelTexture texture(loader.loadTexture("res/front.png"));
	TexturedModel model(rawModel, texture);
	Entity entity(model, glm::vec3(0.0f), 0.0f, 0.0f, 0.0f, 1.0f);

	while (window.isRunning())
	{
		window.clear();
#pragma region USER
		TestShader::inst()->loadView(camera.getViewMatrix());
		//TestShader::inst()->loadProjection(camera.getProjectionMatrix());
		testRenderer.render(entity);
		glCheckError();
#pragma endregion
		Timer::calculateFPS();
		camera.process(&window);
		window.update();
		if (Timer::frameCounter % 60 == 0)
			printf("%d fps\n", Timer::FPS);
	}
}
