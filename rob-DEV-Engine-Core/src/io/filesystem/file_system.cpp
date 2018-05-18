#include "file_system.h"

namespace Engine { namespace Core { namespace IO {
	static VirtualFileSystem* m_Instance = NULL;

	VirtualFileSystem* VirtualFileSystem::getInstance()
	{
		if (m_Instance == NULL)
			m_Instance = new VirtualFileSystem();

		return m_Instance;

	}

	VirtualFileSystem::VirtualFileSystem()
	{
	}

	VirtualFileSystem::VirtualFileSystem(const char* packagedFilePath)
	{
	}

	bool VirtualFileSystem::verifiedChecksum()
	{
		return false;
	}

	VirtualFileSystem::~VirtualFileSystem()
	{
	}
} } }