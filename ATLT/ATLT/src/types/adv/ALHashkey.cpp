#pragma once
#include "../basic/ALLinkedList.cpp"
#include <inttypes.h>
template<typename Hash, typename T>
class ALHashkey {
public:
	Hash ID;
	ALLinkedList<T> values;
	ALHashkey() : ID(0), values(){}
	//ALHashkey(T val) : ID(0), value(val) {}
	//ALHashkey(uint64_t id, T Value) : ID(id), value(Value){}
};