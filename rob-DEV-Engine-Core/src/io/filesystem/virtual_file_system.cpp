#include "virtual_file_system.h"
#include "../common/io.h"

namespace Engine { namespace Core { namespace IO {


	VirtualFileSystem::VirtualFileSystem(const char* VFS_File_Path, VFS_Header_t header)
	{
		this->m_VFS_FilePath = std::string(VFS_File_Path);
		this->m_VFS_Header = header;

		m_InStreamFromDisk.open(VFS_File_Path, std::ios::binary);
		std::cout << (unsigned int)m_InStreamFromDisk.tellg() << "\n";

		//get file of the VFS data = (FULL SIZE) - VFS_HEADER_SIZE 
		m_InStreamFromDisk.seekg(0, std::ios::end);
		m_VFS_DATA_SIZE =  (unsigned int)m_InStreamFromDisk.tellg() - VFS_HEADER_SIZE;

		//no virtual files exist
		if (m_VFS_DATA_SIZE < VF_HEADER_SIZE)
			return;

		//seek to the start of the data
		m_InStreamFromDisk.seekg(VFS_HEADER_SIZE, std::ios::beg);

		//allocate the virtual files to the heap

	}
	
	VirtualFileSystem::~VirtualFileSystem()
	{
		for (size_t i = 0; i < m_VFS_Files.size(); i++)
		{
			delete m_VFS_Files[i];
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

		for (size_t i = 0; i < 128; i++)
		{
			if(i == 127)
				header.vfs_hash[i] = '\0';
			else
				header.vfs_hash[i] = '-';
		}

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

		//print the details of the VFS
		std::cout << "VFS Version:" << temp_header.vfs_version << "\n";
		std::cout << "VFS Hash:" << temp_header.vfs_hash << "\n";
		std::cout << "VFS Dir Count:" << temp_header.vfs_dir_count << "\n";
		std::cout << "VFS File Count:" << temp_header.vfs_dir_count << "\n";

		stream.close();

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
			m_VFS_Files.push_back(fileToAdd);
			return true;
		}

		m_OutStreamToDisk.open(m_VFS_FilePath.c_str(), std::ios::binary | std::ios::app);
		m_OutStreamToDisk.seekp(0, std::ios::end);
		write_to_stream(m_OutStreamToDisk, fileToAdd->m_FileHeader);
		
		for (size_t i = 0; i < fileToAdd->m_FileHeader.file_size; i++)
		{
			write_to_stream(m_OutStreamToDisk, fileToAdd->m_FileData[i]);
		}

		m_OutStreamToDisk.close();
	}

} } }