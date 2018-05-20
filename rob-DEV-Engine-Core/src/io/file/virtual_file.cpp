#include "virtual_file.h"

namespace Engine { namespace Core { namespace IO {
	VirtualFile::VirtualFile(const char* fName, FileType fType, const VF_Data_Param_t& data)
	{
		for (size_t i = 0; i < MAX_FILE_LENGTH; i++)
		{
			if (i < strlen(fName))
				m_FileHeader.vf_name[i] = fName[i];
			else
				m_FileHeader.vf_name[i] = '\0';
		}

		m_FileHeader.vf_size = data.data_byte_size;
		m_FileHeader.vf_type = fType;
		
		m_FileData = data.byte_data;
	}

	VirtualFile::~VirtualFile()
	{
		delete m_FileData;
	}

} } }
