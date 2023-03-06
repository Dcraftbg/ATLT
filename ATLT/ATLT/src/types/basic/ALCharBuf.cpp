#pragma once
#include "../core/ALObj.cpp"
#include "../core/Iterateable.cpp"
#include "../core/Serializeable.cpp"
#include "../core/Printable.cpp"
#include "../../utils/Helpers.cpp"
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>

class ALCharBuf : public ALObj, public Iterateable, public Serializeable, public Printable {
public:
	uint64_t size = 0;
	uint64_t max_size = 0;
	char* ptr;
public:
	ALCharBuf(const uint64_t& size) {
		resize(size);
	}
	ALCharBuf() {
		ptr = nullptr;
	}
	// MAY_THROW_EXCEPTION 
	ALCharBuf(const ALCharBuf& buf) {
		if (buf.ptr == nullptr || buf.size == 0) { this->size = 0; ptr = nullptr; }
		this->size = buf.size + 1;
		this->max_size = this->size;
		this->ptr = (char*)calloc(buf.size, sizeof(char));
		if (this->ptr == nullptr) 
		{
			//TODO: implement some sort of context to the string
			ATLT::pushException(new BasicException(__FUNCTION__, "Calloc could not allocate memory, you probably ran out of heap memory LOL", CPP_EXCEPTION));
			return;
		}
		strcpy_s(this->ptr, buf.size, buf.ptr);
	}
	ALCharBuf(ALCharBuf&& t) noexcept {
		copy(t);
	}
	~ALCharBuf() {
		if (ptr != nullptr) free(ptr);
	}
public:
	void set(const char& c, const uint64_t& pos=0) {
		if (ptr == nullptr) return;
		if (pos > max_size) return;
		ptr[pos] = c;
	}
	// MAY_THROW_EXCEPTION 
	void resize(const uint64_t& size) {
		if (size < this->max_size) return;
		this->max_size = size;
		if (ptr == nullptr){ptr = (char*)calloc(max_size, sizeof(char)); return;}
		void* temp = nullptr;
		temp = realloc(ptr, max_size);
		if (temp == nullptr) {
			free(ptr);
			this->size = 0;
			this->max_size = 0;
			ATLT::pushException(new BasicException(__FUNCTION__, "Realloc could not allocate memory, you probably ran out of heap memory LOL", CPP_EXCEPTION));
		}
		ptr = (char*)temp;
	}
	// MAY_THROW_EXCEPTION 
	void copy(const char* buf) {
		if (buf == nullptr) {
			ATLT::pushException(new BasicException(__FUNCTION__, "Expected buf to be non-null", BASIC_EXCEPTION)); return;
		}
		uint64_t len = strlen(buf);
		if (len > max_size) {
			resize(len + 1);
		}
		size = len;
		strncpy_s(ptr, max_size, buf, len);
	}
	// MAY_THROW_EXCEPTION 
	void copy(const ALCharBuf& buf) {
		if (buf.ptr == nullptr)
		{
			ATLT::pushException(new BasicException(__FUNCTION__, "Expected buf to be non-null", BASIC_EXCEPTION));
			return;
		}
		
		if (buf.size > max_size) {
			resize(buf.size + 1);
		}
		size = buf.size;
		strncpy_s(ptr, max_size, buf.ptr, buf.size);
	}
	// MAY_THROW_EXCEPTION 
	void insert(const char* buf) {
		if (buf == nullptr) {
			ATLT::pushException(new BasicException(__FUNCTION__, "Expected buf to be non-null", BASIC_EXCEPTION)); return;
		}
		uint64_t len = strlen(buf);
		if (size+len > max_size) {
			resize(size+len+ 1);
		}
		strncat_s(ptr, max_size, buf, len);
		size += len;
		//strncpy_s(ptr+offset, buf, len);
	}
	// MAY_THROW_EXCEPTION 
	void insert(const ALCharBuf& buf) {
		if (buf.ptr == nullptr) {
			ATLT::pushException(new BasicException(__FUNCTION__, "Expected buf to be non-null", BASIC_EXCEPTION));
			return;
		}
		if (size+buf.size> max_size) {
			resize(size+buf.size + 1);
		}
		strncat_s(ptr, max_size, buf.ptr, buf.size);
		size += buf.size;
	}
	/***
	uinsert is faster than normal copy but the u indicates that its unsafe
	uinsert basically copies your buffer without safe checking it, like size and if it can even fit
	but instead relies on you to have checked that yourself or be sure that the space actually exists.
	The only few situations I've found it useful is when you want to combine two strings and you have already set the size of them and are sure they can fit.
	***/
	void uinsert(const char* buf) {
		uint64_t len = strlen(buf);
		strncat_s(ptr, max_size, buf, len);
		size += len;
		//strncpy_s(ptr + offset, max_size, buf, strlen(buf));
		//setSection(buf,strlen(buf), offset);
	}
	/***
	uinsert is faster than normal copy but the u indicates that its unsafe
	uinsert basically copies your buffer without safe checking it, like size and if it can even fit
	but instead relies on you to have checked that yourself or be sure that the space actually exists.
	The only few situations I've found it useful is when you want to combine two strings and you have already set the size of them and are sure they can fit.
	***/
	void uinsert(const ALCharBuf& buf) {
		strncat_s(ptr, max_size,buf.ptr, buf.size);
		size += buf.size;
		//strncpy_s(ptr + offset, max_size, buf.ptr, buf.size);
	//	setSection(ptr, buf.size, offset);
	}

public:

	void Serialize(IOBuffer& out) {
		out.write64(max_size);
		out.write64(size);
		out.writestream(size, ptr);
	}
	void Deserialize(IOBuffer& byteData) {
		max_size = byteData.read64();
		size = byteData.read64();
		OStream result = byteData.readstream(size);
		strcpy_s(ptr,size,result.ptr);
	}
	OStream next() {
		OStream out(1);
		out.put(ptr[iterate_index]);
		iterate_index++;
		return out;
	}
	char* getPrinted() {
		return ptr;
	}
};
// REDOING ALCharBuf:
/*
class ALCharBuf : public ALObj, public Iterateable, public Serializeable {
public:
	uint32_t size;
	char* ptr;
public:
	ALCharBuf(uint32_t size) {
		this->size = size;
		ptr = (char*)malloc(size);
	}
	ALCharBuf() {
		size = 0;
		ptr = (char*)malloc(1);
	}
	ALCharBuf(const ALCharBuf& b) {
		//printf("Calling copy constructor: %s, size: %d\n", b.ptr,b.size);
		size = b.size+1;
		ptr = (char*)malloc(size);
		//printf("My size... %d my len() %d", size,strlen(ptr));
		strcpy_s(ptr, b.size, b.ptr);
	}
	~ALCharBuf() {
		free(ptr);
	}
public:
	void resize(unsigned int size) {
		this->size = size;
		void* temp = 0;

		temp = realloc(ptr, size);
		if (temp == NULL) {
			free(ptr);
		}
		ptr = (char*)temp;
	}
public:
	//DEPRECATED
	//char* Serialize() {
	//	struct o {
	//		uint32_t size;
	//		char* ptr;
	//	};
	//	o* p = (o*)malloc(sizeof(size) + size);
	//	if (p != nullptr) {
	//		p->size = size;
	//		strcpy_s(p->ptr,size, ptr);
	//	}
	//	char* out = (char*)malloc(sizeof(size) + size);
	//	if (out == nullptr) exit(1);
	//	*((uint32_t*)out) = size;
	//	char* sOut = out + sizeof(uint32_t);
	//	strcpy_s(sOut, size, ptr);
	//	
	//	//return (char*)p;
	//}
	void Serialize(IOBuffer& out) {
		out.write32(size);
		out.writestream(size, ptr);
	}
	void Deserialize(IOBuffer& byteData) {
		free(ptr);
		size = byteData.read32();
		ptr = (char*)malloc(size);
		if (ptr == nullptr) exit(1);
		strcpy_s(ptr, size, byteData.readstream(size).ptr);
		//ptr = byteData.readstream(size).ptr;
	}
	OStream next() {
		OStream out(1);
		out.put(ptr[iterate_index]);
		iterate_index++;
		return out;
	}

};
*/