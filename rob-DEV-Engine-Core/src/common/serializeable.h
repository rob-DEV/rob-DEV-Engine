#pragma once
class ISerializable
{
public:
	virtual ~ISerializable() {};
	virtual unsigned int getSize() = 0;
};


