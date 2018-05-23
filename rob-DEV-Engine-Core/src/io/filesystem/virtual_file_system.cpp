#include "virtual_file_system.h"
#include "../common/io.h"

namespace Engine { namespace Core { namespace IO {


	VirtualFileSystem::VirtualFileSystem(const char* VFS_File_Path, VFS_Header_t vfs_header)
	{
		this->m_VFS_FilePath = std::string(VFS_File_Path);
		this->m_VFS_Header = vfs_header;

		m_InStreamFromDisk.open(VFS_File_Path, std::ios::binary);

		//get file size of the VFS data = (FULL SIZE) - VFS_HEADER_SIZE 
		m_InStreamFromDisk.seekg(0, std::ios::end);
		m_VFS_RAW_FILE_SIZE = (uint32_t)m_InStreamFromDisk.tellg();
		m_VFS_DATA_SIZE = m_VFS_RAW_FILE_SIZE - VFS_HEADER_SIZE;

		//no virtual files exist
		if (m_VFS_DATA_SIZE < VF_HEADER_SIZE)
			return;

		//seek to the start of the data
		m_InStreamFromDisk.seekg(VFS_HEADER_SIZE, std::ios::beg);

		//allocate the virtual files to the heap
		//packaged files are not null terminated therefore we need to compare sizes for end of files
		while ((uint32_t)m_InStreamFromDisk.tellg() != m_VFS_RAW_FILE_SIZE)
		{
			//handle each virtual file
			VF_Header_t header;
			read_from_stream(m_InStreamFromDisk, header);

			VF_Data_Param_t data;
			data.data_byte_size = header.vf_size;
			data.byte_data = new char[header.vf_size + 1];
			data.byte_data[header.vf_size + 1] = '\0';

			m_InStreamFromDisk.read(reinterpret_cast<char*>(data.byte_data), header.vf_size);
			
			VFS_Files.push_back(new VirtualFile(header.vf_name, header.vf_type, data));
		}

		m_FileSystemOnHeap = true;

	}
	
	VirtualFileSystem::~VirtualFileSystem()
	{
		for (size_t i = 0; i < VFS_Files.size(); i++)
		{
			delete VFS_Files[i];
		}
	}
	
	//CREATING NEW
	VirtualFileSystem* VirtualFileSystem::Create(const char* VFS_File_Path)
	{
		std::ofstream stream;

		stream.open(VFS_File_Path, std::ios::binary | std::ios::out);

		if (!stream.is_open())
		{
			std::cout << "Error opening VFS: \"" << VFS_File_Path << "\"\n";
			return NULL;
		}

		VFS_Header_t header;
		header.vfs_dir_count = 0;
		header.vfs_file_count = 0;
		
		//no null terminator
		for (size_t i = 0; i < 128; i++)
			header.vfs_hash[i] = '-';

		write_to_stream(stream, header);


		stream.close();

		//open the newly created VFS
		return VirtualFileSystem::Open(VFS_File_Path);

	}


	//USE EXISTING
	VirtualFileSystem* VirtualFileSystem::Open(const char* VFS_File_Path)
	{
		std::ifstream stream;

		stream.open(VFS_File_Path, std::ios::binary);

		if (!stream.is_open())
		{
			std::cout << "Error opening VFS: \"" << VFS_File_Path << "\"\n";
			return NULL;
		}

		VFS_Header_t temp_header;
		read_from_stream(stream, temp_header);

		stream.close();
		//allocates the VFS onto the heap
		return new VirtualFileSystem(VFS_File_Path, temp_header);

	}
	
	bool VirtualFileSystem::verifiedHash()
	{
		//in the case of a blank VFS
		if (m_VFS_Header.vfs_dir_count == 0 && m_VFS_Header.vfs_file_count == 0)
			return true;
	}
	
	bool VirtualFileSystem::AddFile(VirtualFile* fileToAdd, bool pushToFile)
	{
		if (!pushToFile)
		{
			VFS_Files.push_back(fileToAdd);
			return true;
		}

		m_OutStreamToDisk.open(m_VFS_FilePath.c_str(), std::ios::binary | std::ios::app);
		m_OutStreamToDisk.seekp(0, std::ios::end);
		write_to_stream(m_OutStreamToDisk, fileToAdd->m_FileHeader);
		
		for (size_t i = 0; i < fileToAdd->m_FileHeader.vf_size; i++)
			write_to_stream(m_OutStreamToDisk, fileToAdd->m_FileData[i]);
		
		m_OutStreamToDisk.close();
		
		//mount in RAM
		VFS_Files.push_back(fileToAdd);
	}




	//TODO: refactor this to a common methods file
	bool str_ch_by_ch_cmp(const char* a, const char* b)
	{
		for (size_t i = 0; i < strlen(a); i++)
			if (a[i] != b[i])
				return false;
		return true;
	}


	VirtualFile* VirtualFileSystem::Retrieve(const char* fileName)
	{
		for (int i = 0; i < VFS_Files.size(); i++)
			if (str_ch_by_ch_cmp(VFS_Files[i]->m_FileHeader.vf_name, fileName))
				return VFS_Files[i];
		
		return NULL;
	}

} } }