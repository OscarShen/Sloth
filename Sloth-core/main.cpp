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
	Shader shader("src/shader/basic.vert", "src/shader/basic.frag");
	std::vector<Renderable2D*> sprites;
#if BATCH
	StaticSprite sprite(5, 5, 4, 4, glm::vec4(1.0f, 0.0f, 1.0f, 1.0f), shader);
	StaticSprite sprite2(7,1,2,3, glm::vec4(0.2f, 0.0f, 1.0f, 1.0f), shader);
	Simple2DRender render;
#else
	Sprite sprite(5, 5, 4, 4, glm::vec4(1.0f, 0.0f, 1.0f, 1.0f));
	Sprite sprite2(7, 1, 2, 3, glm::vec4(0.2f, 0.0f, 1.0f, 1.0f));
	BatchRenderer2D render;

	for (float i = 0; i < 16.0f; i += 0.5f) {
		for (float j = 0; j < 12.0f; j += 0.5f) {
			sprites.push_back(new Sprite(i, j, 1.2f, 1.2f, glm::vec4(rand() % 1000 / 1000.0f, 0.0f, 1.0f, 1.0f)));
		}
	}

#endif
	double x, y;
	shader.use();
	glm::mat4 projection = glm::ortho(0.0f, 16.0f, 0.0f, 12.0f, -1.0f, 1.0f);
	shader.SetMatrix4("projection", projection, GL_TRUE);
	while (!window.closed())
	{
		window.clear();
		window.getCursorPos(x, y);
		shader.SetVector2f("light_pos", (GLfloat)(x), (GLfloat)((600 - y)));
		render.begin();
		//render.sumbit(&sprite);
		//render.sumbit(&sprite2);
		for (int i = 0; i < sprites.size(); ++i) {
			render.sumbit(sprites[i]);
		}
		render.end();
glCheckError();
		render.flush();
		window.update();
	}
}
