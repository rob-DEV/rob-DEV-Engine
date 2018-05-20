#pragma once
#include <string>
#include "../common/file_types.h"

namespace Engine { namespace Core { namespace IO {

	class VirtualFile
	{
	private:
		
	public:
		VF_Header_t m_FileHeader;
		char* m_FileData;

		VirtualFile(const char* fName, FileType fType, const VF_Data_Param_t& data);
		~VirtualFile();

	};
} } }
