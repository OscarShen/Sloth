#include "src/graphics/window.h"
#include "src/graphics/shader.h"
#include "src/graphics/buffers/buffer.h"
#include "src/graphics/buffers/vertex_array.h"
#include "src/graphics/buffers/index_buffer.h"
#include "src/utils/error_check.h"
#include "src/graphics/simple_2d_renderer.h"
#include "src/graphics/static_sprite.h"
#include "src/graphics/batch_renderer_2d.h"
#include "src/graphics/sprite.h"
#include "src/utils/timer.h"
#include "src/graphics/layers/tile_layer.h"


#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
using namespace sloth;
using namespace graphics;
using namespace util;

#define BATCH 0
int main()
{

	Window window("Sloth!", 800, 600);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	Shader *s = new Shader("src/shader/basic.vert", "src/shader/basic.frag");
	Shader &shader = *s;
	shader.use();

	TileLayer layer(&shader);
	for (float x = -16.0f; x < 16.0f; x+=0.16f)
	{
		for (float y = -12.0f; y < 16.0f; y+=0.12f)
		{
			layer.add(new Sprite(x, y, 0.16f, 0.12f, glm::vec4(rand() % 1000 / 1000.0f, 0, 1, 1)));
		}
	}

	Timer time;
	float timer = 0;
	unsigned int frames = 0;
	double x, y;
	shader.enable();
	while (!window.closed())
	{
		window.clear();
		window.getCursorPos(x, y);

		shader.SetVector2f("light_pos", (GLfloat)(x), (GLfloat)((window.getHeight() - y)));

		layer.render();

		window.update();
		++frames;
		if (time.elapsed() - timer > 1.0f)
		{
			timer += 1.0f;
			printf("%d fps\n", frames);
			frames = 0;
		}
	}
}
