#pragma once
#include "../core/Iterateable.cpp"
#include <assert.h>
// TODO: Implement serializing for ALArrays
template <typename T, uint64_t max_size>
class ALArray : public Iterateable{
	T ar[max_size] = {0};
	uint64_t size=0;
public:
	ALArray() {

	}
	T* getRaw() {
		return ar;
	}
	T get(uint64_t index) {
		if (index < 0 || index > max_size) return 0;

		return ar[index];
	}
	uint64_t getSize() {
		return size;
	}
	uint64_t getMaxSize() {
		return max_size;
	}
	bool push(const T& m) {
		if (size >= max_size) return 1;
		ar[size] = m;
		size++;
		return 0;
	}
	T pop() {
		if (!size) return T();
		T out = ar[size-1];
		size--;
		return out;
	}
public:
	virtual OStream next() {
		if (iterate_index >= max_size) return OStream();
		OStream out(sizeof(T)+1);
		memcpy_s(out.ptr, out.size, &ar[iterate_index], sizeof(T));
		iterate_index++;
		return out;
	}
};