#include "timer.h"

namespace sloth { 

	double Timer::start = static_cast<float>(glfwGetTime());
	double Timer::lastFrameTime = start;
	double Timer::currentFrameTime = start;
	double Timer::deltaFrameTime = 1.0f / 60.0f;
	int Timer::FPS = 60;
	unsigned int Timer::frameCounter = 0;

	void Timer::reset()
	{
		start = 0.0;
	}

	double Timer::elapsed()
	{
		return glfwGetTime() - start;
	}

	void Timer::calculateFPS()
	{
		++frameCounter;
		currentFrameTime = glfwGetTime();
		deltaFrameTime = currentFrameTime - lastFrameTime;
		lastFrameTime = currentFrameTime;
		FPS = static_cast<int>(1.0 / deltaFrameTime);
	}

} 
