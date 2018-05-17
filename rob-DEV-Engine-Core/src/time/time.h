#pragma once
#include <Windows.h>
#include "../common/singleton_instance.h"

#define TIME Time::getInstance()

namespace Engine { namespace Core {
	class Time : public Singleton_Instance
	{
	private:
		LARGE_INTEGER m_Start;
		double m_Frequency;
		double m_LastTime;
	public:
		double deltaTime;

		Time();
		~Time();
		void reset();
		double elasped();
		static Time* getInstance();
	};
} }

