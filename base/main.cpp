#include "engine/MainComponent.h"
#include "engine/Window.h"
#include "engine/Time.h"

#include <iostream>

const int WIDTH = 800;
const int HEIGHT = 600;
const char *TITLE = "SLOTH";

void main() {
	Window window;
	window.createWindow(WIDTH, HEIGHT, TITLE);

	MainComponent m(window);
	m.start();
}