#include "time.h"
#include <ctime>

namespace Engine { namespace Core {
	static Time* m_Instance = NULL;
	Time* Time::getInstance()
	{
		if (m_Instance == NULL)
			m_Instance = new Time();

		return m_Instance;
	}
	Time::Time()
	{
		//ensure random are "random"
		srand(time(NULL));
		
		m_LastTime = 0;
		deltaTime = 0;

		LARGE_INTEGER frequency;
		QueryPerformanceFrequency(&frequency);
		m_Frequency = 1.0 / frequency.QuadPart;
		QueryPerformanceCounter(&m_Start);
	}


	Time::~Time()
	{
	}

	void Time::reset()
	{
		QueryPerformanceCounter(&m_Start);
	}

	double Time::elasped()
	{
		LARGE_INTEGER current;
		QueryPerformanceCounter(&current);
		unsigned __int64 cycles = current.QuadPart - m_Start.QuadPart;

		deltaTime = (float)(cycles * m_Frequency) - m_LastTime;
		m_LastTime = (float)(cycles * m_Frequency);

		return (float)(cycles * m_Frequency);
	}
} }