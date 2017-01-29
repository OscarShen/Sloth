#pragma once
#ifndef SLOTH_TIMER_H_
#define SLOTH_TIMER_H_

#include <Windows.h>
#include <GLFW/glfw3.h>

namespace sloth { namespace util {

	class Timer
	{
	public:
		static double start;
		static double lastFrameTime;
		static double currentFrameTime;
		static double deltaFrameTime;
		static int FPS;
		static unsigned int frameCounter;

		static void reset();
		static double elapsed();
		static void calculateFPS();
	};

} }


#endif // !SLOTH_TIMER_H_
