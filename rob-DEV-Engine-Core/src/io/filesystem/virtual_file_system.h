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
		
		//GLOBAL HEADER FOR THE VFS
		VFS_Header_t m_VFS_Header;

		//ENTIRE RAW BYTES SIZE FOR THE VFS FILE
		unsigned int m_VFS_RAW_FILE_SIZE;
		
		//ENTIRE RAW BYTES SIZE FOR THE VFS FILE - VFS_HEADER_SIZE
		unsigned int m_VFS_DATA_SIZE;

		bool m_FileSystemOnHeap = false;

		//EXIST VFS FILE
		bool verifiedHash();
	public:
		std::vector<VirtualFile*> VFS_Files;
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
