#include "Game.h"
#include "Input.h"

#include <iostream>
Game::Game()
{
	shouldClose = false;
}

void Game::input()
{
	if (Input::isKeyPressed(SLOTH_KEY_W)) {
		std::cout << "W" << std::endl;
	}
	if (Input::isKeyPressed(SLOTH_KEY_ESCAPE)) {
		this->setShouldClose(true);
		std::cout << "CLOSE" << std::endl;
	}
}

void Game::update()
{
}

void Game::render()
{
}

bool Game::shouldGameClose() const
{
	return shouldClose;
}

void Game::setShouldClose(bool shouldClose)
{
	this->shouldClose = shouldClose;
}
