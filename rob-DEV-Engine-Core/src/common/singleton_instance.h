#pragma once

#ifndef NULL
	#define NULL 0
#endif // !NULL


struct Singleton_Instance {
	//NULL
	static inline Singleton_Instance* getInstance() { return 0; }
};