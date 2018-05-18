#pragma once
#include "../../common/singleton_instance.h"

namespace Engine { namespace Core { namespace IO {
	class VirtualFileSystem : public Singleton_Instance
	{
	private:
		bool verifiedChecksum();
	public:
		VirtualFileSystem();
		VirtualFileSystem(const char* packagedFilePath);
		~VirtualFileSystem();
		static VirtualFileSystem* getInstance();

	};
} } }
