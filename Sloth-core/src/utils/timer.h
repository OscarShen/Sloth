#pragma once
#ifndef SLOTH_TIMER_H_
#define SLOTH_TIMER_H_

#include <sloth.h>
#include <Windows.h>

namespace sloth {

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

} 

#endif // !SLOTH_TIMER_H_
