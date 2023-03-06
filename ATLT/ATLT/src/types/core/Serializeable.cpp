#pragma once
#include "IOBuffer.cpp"
class Serializeable{
public:
	virtual void Deserialize(IOBuffer& byteData) = 0;
	virtual void Serialize(IOBuffer& out)        = 0;
};