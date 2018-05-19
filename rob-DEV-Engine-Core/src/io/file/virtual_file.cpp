#include "virtual_file.h"

namespace Engine { namespace Core { namespace IO {
	VirtualFile::VirtualFile(const char* fName, FileType fType, const VF_Data_t& data)
	{
		//name
		for (size_t i = 0; i < MAX_FILE_LENGTH; i++)
		{
			if (i < strlen(fName))
				m_FileHeader.file_name[i] = fName[i];
			else
				m_FileHeader.file_name[i] = '\0';
		}

		m_FileHeader.file_size = data.data_byte_size;
		m_FileHeader.file_type = fType;
		
		m_FileData = data.byte_data;
	}


	VirtualFile::~VirtualFile()
	{
	}
} } }