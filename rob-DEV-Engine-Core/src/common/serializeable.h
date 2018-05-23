#pragma once

namespace Engine { namespace Core {

	class ISerializable
	{
	public:
		virtual ~ISerializable() {};
		virtual unsigned int getSize() = 0;
	};

} }