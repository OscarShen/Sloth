#pragma once
#ifndef SLOTH_TIMER_H_
#define SLOTH_TIMER_H_

#include <Windows.h>

namespace sloth { namespace util {

	class Timer
	{
	private:
		LARGE_INTEGER m_Start;
		double m_Frequency;

	public:
		Timer()
		{
			LARGE_INTEGER frequency;
			QueryPerformanceFrequency(&frequency);
			m_Frequency = 1.0f / frequency.QuadPart;
			QueryPerformanceCounter(&m_Start);
		}

		void reset()
		{
			QueryPerformanceCounter(&m_Start);
		}

		float elapsed()
		{
			LARGE_INTEGER current;
			QueryPerformanceCounter(&current);
			unsigned __int64 cycles = current.QuadPart - m_Start.QuadPart;
			return static_cast<float>(cycles * m_Frequency);
		}
	};


} }


#endif // !SLOTH_TIMER_H_
