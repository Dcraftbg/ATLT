#pragma once
#include <inttypes.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
//#include "../ATLT/ATLT/ALString.h"
class OStream {
public:
	char* ptr=nullptr;
	uint64_t size = 0;
	uint64_t max_size = 0;
public:
	OStream(const char* p) { 
		uint64_t len = strlen(p);
		resize(len+1); 
		strncpy_s(ptr, max_size, p,len);
		size = len;
	}
	OStream(uint64_t size) {resize(size);}
	OStream() {ptr = nullptr;}
	OStream(const OStream& o) {
		resize(o.size);
		strncpy_s(ptr, max_size,o.ptr, o.size);
		size = o.size;
	}
	OStream(OStream&& t) noexcept {
		resize(t.size);
		strncpy_s(ptr, max_size, t.ptr, t.size);
		size = t.size;
	}
	~OStream() {
		if (ptr != nullptr) free(ptr);
	}
public:
	void resize(uint64_t size) {
		if (size < this->max_size) return;
		this->max_size = size;
		if (ptr == nullptr) { ptr = (char*)calloc(max_size, sizeof(char)); return; }
		void* temp = nullptr;
		temp = realloc(ptr, max_size);
		if (temp == nullptr) {
			free(ptr);
			this->size = 0;
			this->max_size = 0;
		}
		ptr = (char*)temp;
	}
	void zeroInit() {
		memset(ptr, 0, size);
		size = 0;
	}
	void put(char c) {
		resize(size + 1);
		ptr[size] = c;
	}
	void put16(uint16_t i) {
		#ifdef USE_DEPRECATED
		resize(size + sizeof(uint16_t));
		*((uint16_t*)(ptr + size)) = i;
		size+=sizeof(uint16_t);
		#else
		fprintf(stderr, "ERROR: Put16 is deprecated and possibly might not work!\nDefine USE_DEPRECATED to be able to use it\n");
		exit(1);
		#endif	
	}
	void put32(uint32_t i) {
		#ifdef USE_DEPRECATED
		resize(size + sizeof(uint32_t));
		*((uint32_t*)(ptr + size)) = i;
		size += sizeof(uint32_t);
		#else
		fprintf(stderr, "ERROR: Put32 is deprecated and possibly might not work!\nDefine USE_DEPRECATED to be able to use it\n");
		exit(1);
		#endif	
	}
	void put64(uint64_t i) {
		#ifdef USE_DEPRECATED
		resize(size + sizeof(uint64_t));
		*((uint64_t*)(ptr + size)) = i;
		size += sizeof(uint64_t);
		#else
		fprintf(stderr, "ERROR: Put64 is deprecated and possibly might not work!\nDefine USE_DEPRECATED to be able to use it\n");
		exit(1);
		#endif	
	}
	/*static OStream toOStream(ALString& str) {
		OStream out(str.size());
		strcpy_s(out.ptr, str.size(), str.getRawBuf().ptr);
		return out;
	}*/
};

//class OStream {
//public:
//	char* ptr;
//	uint32_t size;
//public:
//	OStream(uint32_t size) {
//		ptr = (char*)malloc(size);
//		this->size = size;
//	}
//	OStream() {
//		ptr = (char*)malloc(1);
//		this->size = 0;
//	}
//	OStream(const OStream& o) {
//		ptr = (char*)malloc(1);
//		resize(o.size+1);
//		strcpy_s(ptr, size, o.ptr);
//	}
//	~OStream() {
//		//printf("\nCLEANING OSTREAM ptr: %p %s\n", ptr,ptr);
//		free(ptr);
//	}
//public:
//	void resize(unsigned int size) {
//		this->size = size;
//		void* temp = 0;
//		temp = realloc(ptr, size);
//		if (temp == NULL) {
//			free(ptr);
//		}
//		ptr = (char*)temp;
//	}
//	void zeroInit() {
//		memset(ptr, 0, size);
//	}
//	void put(char c) {
//		resize(size + 1);
//		ptr[size] = c;
//	}
//	void put16(uint16_t i) {
//		void* tmp = realloc(ptr, size + sizeof(uint16_t));
//		if (tmp == nullptr) {
//			exit(1);
//		}
//		ptr = (char*)tmp;
//		*((uint16_t*)(ptr+size)) = i;
//		size+=sizeof(uint16_t);
//
//	}
//	void put32(uint32_t i) {
//		void* tmp = realloc(ptr, size + sizeof(uint32_t));
//		if (tmp == nullptr) {
//			exit(1);
//		}
//		ptr = (char*)tmp;
//		*((uint32_t*)(ptr + size)) = i;
//		size += sizeof(uint32_t);
//	}
//	void put64(uint32_t i) {
//		void* tmp = realloc(ptr, size + sizeof(uint64_t));
//		if (tmp == nullptr) {
//			exit(1);
//		}
//		ptr = (char*)tmp;
//		*((uint64_t*)(ptr + size)) = i;
//		size += sizeof(uint64_t);
//	}
//};