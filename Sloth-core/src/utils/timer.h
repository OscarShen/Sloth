#pragma once
#ifndef SLOTH_TIMER_H_
#define SLOTH_TIMER_H_

#include <Windows.h>
#include <GLFW/glfw3.h>

namespace sloth { namespace util {

	class Timer
	{
	private:
		double m_Start;
		double m_LastFrameTime;
		double m_CurrentFrameTime;
		double m_DeltaFrameTime;
		int m_FPS;
		unsigned int m_FrameCounter;

	public:
		Timer();
		void reset();
		double elapsed();
		void calculateFPS();

		inline double getDeltaFrameTime()const { return m_DeltaFrameTime; }
		inline int getFPS() const { return m_FPS; }
		inline unsigned int getFramerCounter() const{ return m_FrameCounter; }
	};

} }


#endif // !SLOTH_TIMER_H_
