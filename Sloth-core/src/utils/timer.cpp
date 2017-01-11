#include "timer.h"

namespace sloth { namespace util {
	Timer::Timer()
		:m_FPS(0), m_FrameCounter(0)
	{
		m_Start = glfwGetTime();
		m_LastFrameTime = m_Start;
		m_CurrentFrameTime = m_Start;
		m_DeltaFrameTime = 0.0;
	}

	void Timer::reset()
	{
		m_Start = 0.0;
	}

	double Timer::elapsed()
	{
		return glfwGetTime() - m_Start;
	}

	void Timer::calculateFPS()
	{
		++m_FrameCounter;
		m_CurrentFrameTime = glfwGetTime();
		m_DeltaFrameTime = m_CurrentFrameTime - m_LastFrameTime;
		m_LastFrameTime = m_CurrentFrameTime;
		m_FPS = 1.0 / m_DeltaFrameTime;
	}

} }
