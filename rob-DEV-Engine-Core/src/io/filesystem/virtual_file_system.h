#pragma once
#include <fstream>
#include <iostream>
#include <vector>

#include "../../common/singleton_instance.h"
#include "../file/virtual_file.h"

/*
*	STRUCTURE OF A .VFS FILE (NN == NO NULL TERMINATOR USED FOR THIS STRUTURE)
*	VFS_Header_t (148 bytes)
*		vfs_marker - <VFS> NN
*		vfs_version - <V1.00> NN
*		vfs_hash -  <128 byte HASH> NN
*		vfs_dir_count - uint32 NN
*		vfs_file_count - uint32 NN
*	FOREACH FILE
*	VF_Header_t (148 bytes)
*		vf_marker - <VFS--FILE>
*		vf_name - MAX LENGTH 128 bytes
*		vf_type -  uint32 NN
*		vf_size - uint32 NN
*	FOLLOWED BY FILE DATA
*/

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
		VirtualFile* Retrieve(const char* fileName);

		//CREATE NEW
		static VirtualFileSystem* Create(const char* VFS_File_Path);
		//EXIST VFS FILE
		static VirtualFileSystem* Open(const char* VFS_File_Path);
		
	};
} } }
