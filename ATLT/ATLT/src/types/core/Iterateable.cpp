#pragma once
#include "OStream.cpp"
class Iterateable {
protected:
	uint64_t iterate_index=0;
public:
	virtual OStream next() = 0;
};