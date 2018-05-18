#pragma once
#include "../common/file_types.h"

namespace Engine { namespace Core { namespace IO {
	class VirtualFile
	{
	private:
		FileType type;
	public:
		VirtualFile();
		~VirtualFile();
	};
} } }
