#pragma once
#ifndef SLOTH_MAINCOMPONENT_H_
#define SLOTH_MAINCOMPONENT_H_
#include "Window.h"
#include "Game.h"
class MainComponent
{
public:
	MainComponent(Window &window);
	~MainComponent();

	void start();

	void stop();

	void run();

	void render();

	void cleanUp();

private:
	Window *window;
	Game *game;
};
#endif // !SLOTH_MAINCOMPONENT_H_