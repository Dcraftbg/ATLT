#pragma once
#include <inttypes.h>
#include "OStream.cpp"
class IOBuffer {
public:
	virtual void write(char out)		      = 0;
	virtual void write16(uint16_t out)        = 0;
	virtual void write32(uint32_t out)        = 0;
	virtual void write64(uint64_t out)        = 0;
	virtual void writestream(uint64_t size, char* data) = 0;
	virtual void writestream(OStream stream)  = 0;
	
public:
	virtual char read()                       = 0;
	virtual uint16_t read16()                 = 0;
	virtual uint32_t read32()                 = 0;
	virtual uint64_t read64()				  = 0;
	virtual OStream readstream(uint64_t size) = 0;
};