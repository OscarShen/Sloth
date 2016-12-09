#include "src/graphics/window.h"
#include "src/utils/fileutils.h"
#include "src/graphics/shader.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
int main() 
{
	using namespace sloth;
	using namespace graphics;

	Window window("Sloth!", 800, 600);
	glClearColor(1.0f, 0.0f, 1.0f, 1.0f);

	Shader shader;
	shader.Compile("src/shader/basic.vert", "src/shader/basic.frag");

	while (!window.closed())
	{
		window.clear();
		window.update();
	}
}
