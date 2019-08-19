#pragma once
#include <fstream>
#include <istream>
#include <ostream>

namespace Engine { namespace Core { namespace IO {

	template<typename T>
	inline void read_from_stream(std::ifstream& stream, T& t)
	{
		stream.read(reinterpret_cast<char*>(&t), sizeof(T));
	}

	template<typename T>
	inline void read_from_stream(std::ifstream& stream, T& buffer, uint32_t size)
	{
		stream.read(reinterpret_cast<char*>(&buffer), size);
	}


	template<typename T>
	inline void write_to_stream(std::ofstream& stream, T& t)
	{
		stream.write(reinterpret_cast<char*>(&t), sizeof(T));
	}

	
} } }