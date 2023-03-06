#pragma once
#include "../core/ALObj.cpp"
#include "../core/Iterateable.cpp"
#include "../core/Serializeable.cpp"
#include "../../utils/Helpers.cpp"
//#include "ALListElement.cpp"
//TODO: Redesign ALList to use new max_size stuff.
template<typename T>
class ALList : public ALObj, public Iterateable, public Serializeable
{
private:
	uint32_t count = 0;
	T* list;
public:
	ALList() {
		list = (T*)calloc(1, sizeof(T));
		count = 0;
	}
	ALList(const uint32_t& count) {
		list = (T*)calloc(count,sizeof(T));
		this->count = count;
	}
	~ALList() {
		free(list);
	}

public:
	uint32_t getCount() {
		return count;
	}
	void resize(uint32_t count) {
		void* temp = realloc(list, count * sizeof(T));
		if (temp == nullptr) {
			free(list);
			ATLT::pushException(new BasicException(__FUNCTION__, "Realloc could not allocate memory, you probably ran out of heap memory LOL", CPP_EXCEPTION));
			return;
		}
		list = (T*)temp;
		this->count = count;
	}
	T* getRaw() {
		return list;
	}
	void push(T val) {
		resize(count + 1);
		list[count - 1] = val;
		///list[count - 1].empty = false;
	}
	T pop() {
		T o = list[count - 1];
			//this->resize(count - 1);
		resize(count - 1);
		count--;
		return o;
	}
	T& get(uint32_t pos) {
		return list[pos];
	}
	void set(uint32_t pos, T value) {
		list[pos] = value;
	}
public:
	void Deserialize(IOBuffer& byteData) {
		count = byteData.read32();
		//char* from = byteData.readstream(count * sizeof(T)).ptr;
		resize(count);
		T* from = (T*)byteData.readstream(count * sizeof(T)).ptr;
		for (uint32_t i = 0; i < count; i++) {
			list[i] = from[i];
		}
	};
	void Serialize(IOBuffer& out) {
		out.write32(count);
		// TODO: Implement checking for if object is serializeable or not
		out.writestream(count*sizeof(T), (char*)list);
	};
	OStream next() {
		OStream out(sizeof(T));
		*((T*)out.ptr) = list[iterate_index];
		iterate_index++;
		return out;
	}
};
