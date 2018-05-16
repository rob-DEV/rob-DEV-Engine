#pragma once
#include "../common/singleton_instance.h"

namespace Engine { namespace Core {
	class Time : public Singleton_Instance
	{
	public:
		Time();
		~Time();
		static Time* getInstance();
	};
} }

