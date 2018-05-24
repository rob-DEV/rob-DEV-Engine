#pragma once

namespace Engine { namespace Core {

	class ISerializable
	{
	public:
		virtual ~ISerializable() {};
		virtual uint32_t getSize() = 0;
	};

} }