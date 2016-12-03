#include "MainComponent.h"
#include "Time.h"
#include "Game.h"

#include <iostream>
#include <Windows.h>

MainComponent::MainComponent(Window & window)
{
	this->window = &window;
	game = new Game();
}

MainComponent::~MainComponent()
{
	delete game;
}

void MainComponent::start() {
	run();
}

void MainComponent::stop()
{
	window->stop();
	cleanUp();
}

void MainComponent::run() {
	game->setShouldClose(false);

	int frames = 0;
	double frameCounter = 0.0;

	double lastTime = Time::getTime();
	const double frameTime = 1.0 / window->getFrameCap();
	Time::setDelta(frameTime);
	double unprocessedTime = 0.0;

	while (!game->shouldGameClose()) {
		bool render = false;
		double currentTime = Time::getTime();
		double deltaTime = currentTime - lastTime;
		lastTime = currentTime;
		unprocessedTime += deltaTime;
		frameCounter += deltaTime;

		while (unprocessedTime > frameTime) {
			render = true;
			unprocessedTime -= frameTime;

			game->input();
			game->update();

			if (frameCounter >= 1.0) {
				std::cout << frames << std::endl;
				frames = 0;
				frameCounter = 0.0;
			}
		}


		if (render) {
			game->render();
			MainComponent::render();
			++frames;
		}
		else {
			try
			{
				Sleep(1);
			}
			catch (const std::exception&)
			{

			}
		}
	}
	stop();
}

void MainComponent::render()
{
	window->render();
}

void MainComponent::cleanUp()
{
	window->dispose();
}
