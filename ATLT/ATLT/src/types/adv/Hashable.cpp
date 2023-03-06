#pragma once
#include <inttypes.h>
class Hashable {
public:
	virtual uint64_t hash() const = 0;
};