#pragma once

namespace Engine { namespace Core { namespace IO {
	//A list of virtual file types read in from packaged files
	enum FileType{ TEXT, PNG, JPG, OBJ, SCENE};

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
		char vf_marker[12] = { '<', 'V', 'F', 'S', '-','-', 'F', 'I','L', 'E', '>', '\0' };
		char vf_name[MAX_FILE_LENGTH];
		FileType vf_type;
		unsigned int vf_size;

	} VF_Header_t;

	//Grouping for single parameter passing
	typedef struct Virtual_File_Data
	{
		char* byte_data;
		unsigned int data_byte_size;

	public:
		Virtual_File_Data() { };
		template<typename T>
		Virtual_File_Data(T& data, unsigned int size)
		{
			data_byte_size = size;
			byte_data = new char[data_byte_size + 1];
			byte_data[data_byte_size + 1] = NULL;

			memcpy(byte_data, &data, data_byte_size);
		}

	} VF_Data_Param_t;


	#define VFS_HEADER_SIZE sizeof(VFS_Header_t)
	#define VF_HEADER_SIZE sizeof(VF_Header_t)

} } }