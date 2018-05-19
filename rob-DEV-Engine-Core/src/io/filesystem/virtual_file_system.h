#pragma once
#include <fstream>
#include <iostream>
#include <vector>

#include "../../common/singleton_instance.h"
#include "../file/virtual_file.h"


namespace Engine { namespace Core { namespace IO {
	class VirtualFileSystem
	{
	private:

		std::ofstream m_OutStreamToDisk;
		std::ifstream m_InStreamFromDisk;

		std::string m_VFS_FilePath;
		
		//DATA
		VFS_Header_t m_VFS_Header;
		std::vector<VirtualFile*> m_VFS_Files;
		//Excluding the VFS_Header
		unsigned int m_VFS_DATA_SIZE;

		bool m_FileSystemOnHeap = false;
		//END DATA

		//EXIST VFS FILE
		bool verifiedHash();

	public:
		VirtualFileSystem(const char* VFS_File_Path, VFS_Header_t header);
		~VirtualFileSystem();

		bool AddFile(VirtualFile* fileToAdd, bool pushToFile);

		//CREATE NEW
		static VirtualFileSystem* Create(const char* VFS_File_Path);
		//EXIST VFS FILE
		static VirtualFileSystem* Open(const char* VFS_File_Path);
		
	};
} } }
