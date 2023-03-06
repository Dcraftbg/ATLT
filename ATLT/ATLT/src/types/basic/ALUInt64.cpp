#pragma once
#include <inttypes.h>
#include "../adv/Hashable.cpp"
class ALUInt64 : public Hashable{
public:
	ALUInt64(uint64_t value) : value_(value) {}
	operator uint64_t() const { return value_; }
private:
	uint64_t value_;
public:
	virtual uint64_t hash() const {
		return value_;
	}
};