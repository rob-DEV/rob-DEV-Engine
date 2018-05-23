#pragma once
namespace Engine { namespace Core {

	//Aware that this does nothing but it's a reminder to use getInstance()
	struct Singleton_Instance {
		//NULL
		static inline Singleton_Instance* getInstance() { return 0; }
	};

} }