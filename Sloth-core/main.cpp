#include "src/graphics/window.h"
#include "src/graphics/shader.h"
#include "src/graphics/buffers/buffer.h"
#include "src/graphics/buffers/vertex_array.h"
#include "src/graphics/buffers/index_buffer.h"
#include "src/utils/error_check.h"
#include "src/graphics/simple_2d_renderer.h"


#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
using namespace sloth;
using namespace graphics;
using namespace util;
int main()
{

	Window window("Sloth!", 800, 600);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	Shader shader("src/shader/basic.vert", "src/shader/basic.frag");
	Renderable2D sprite(glm::vec3(5.0f, 5.0f, 0.0f), glm::vec2(4.0f, 4.0f), glm::vec4(1.0f, 0.0f, 1.0f, 1.0f), &shader);
	Simple2DRender render;
	double x, y;
	shader.use();
	glm::mat4 projection = glm::ortho(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f);
	shader.SetMatrix4("projection", projection, GL_TRUE);
	while (!window.closed())
	{
		window.clear();
		window.getCursorPos(x, y);
		shader.SetVector2f("light_pos", (GLfloat)(x), (GLfloat)((600 - y)));
		render.sumbit(&sprite);
		render.flush();
		window.update();
	}
}
