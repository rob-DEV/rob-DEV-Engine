#pragma once

namespace Engine { namespace Core { namespace IO {
	//A list of virtual file types read in from packaged files
	enum FileType{ TEXT, PNG, JPG, OBJ};

	#define MAX_FILE_LENGTH 128

	//padded rather than __packed 148 bytes
	typedef struct Virtual_FileSystem_Header
	{
		char vfs_marker[5] = { '<', 'V','F','S', '>' };
		char vfs_version[7] = { '<', 'V','1','.', '0','0', '>' };
		char vfs_hash[MAX_FILE_LENGTH];
		unsigned int vfs_dir_count;
		unsigned int vfs_file_count;

	} VFS_Header_t;

	//4GB limit :( again 148 bytes
	typedef struct Virtual_File_Header
	{
		char vfs_vf_marker[12] = { '<', 'V', 'F', 'S', '-','-','-', 'F', 'I','L', 'E', '>' };
		char file_name[MAX_FILE_LENGTH];
		FileType file_type;
		unsigned int file_size;

	} VF_Header_t;

	typedef struct Virtual_File_Data
	{
		char* byte_data;
		unsigned int data_byte_size;
	} VF_Data_t;


	#define VFS_HEADER_SIZE sizeof(VFS_Header_t)
	#define VF_HEADER_SIZE sizeof(VF_Header_t)

} } }