#pragma once
#include "../core/ALObj.cpp"
#include "../adv/Hashable.cpp"
#include "../core/Printable.cpp"
#include "../../utils/Helpers.cpp"
#include "ALCharBuf.cpp"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <inttypes.h>
class ALString : public ALObj, public Iterateable, public Serializeable, public IOBuffer, public Hashable, public Printable
{
private:
	ALCharBuf buf;
public:
	ALString() : buf(0) {}
	ALString(const uint64_t& size) : buf(size) {}
	ALString(const ALCharBuf& str) { buf.copy(str); }
	ALString(const ALString& str) {buf.copy(str.buf);}
	ALString(ALString&& str) noexcept { buf.copy(str.buf); }
	ALString(const char* str) { buf.copy(str); }
	~ALString() {}
public:
	void resize(const uint32_t& size) {
		buf.resize(size);
	}
	char* c_str() {
		return buf.ptr;
	}
	ALCharBuf& getRawBuf() {
		return buf;
	}
	uint64_t size() {
		return buf.size;
	}
	/***
	Not to be confused with isEmpty, is going to also check if the max_size < buf.size and only if buf.ptr == nullptr not that the ptr has actual data pointed to it;
	***/
	bool isValid() {
		return buf.ptr == nullptr || buf.max_size < buf.size;
	}
	/***
	Checks if the string is empty
	***/
	bool isEmpty() {
		return buf.ptr == nullptr || !buf.ptr;
	}
	/***
	If you get around to using this function, you might consider refactoring your code to use functions like insert or copy which would automatically update the size for you,
	where as using this function would cause another strlen call if one had previously occured. If you can't possibly do it without them (or manually doing it yourself in a faster way) then calling the function would update the size
	of the string
	***/
	void update() {
		buf.size = strlen(buf.ptr);
	}
	void putc(const char& c) {
		resize(buf.size + 1);
		buf.ptr[buf.size] = c;
	}
	void zeroInit() {memset(buf.ptr, 0, buf.max_size);}
	/***
	One thing to note here, is that clear does not zero fill the full buffer but instead only the part thats taken up by 'size'
	Call zeroInit for full clear of the buffer
	***/
	void clear() {memset(buf.ptr, 0, buf.size);}
	void operator=(const char* str) {
		buf.copy(str);
	}
	void operator=(const ALCharBuf& str) {
		buf.copy(str);
	}
	// MAY_THROW_EXCEPTION 
	void insert(const char* b) {
		buf.insert(b);
	}
	// MAY_THROW_EXCEPTION 
	void insert(const ALCharBuf& b) {
		this->buf.insert(b);
	}
	void insert(const ALString& b) {
		this->buf.insert(b.buf);
	}
	void copy(const ALString& b) {
		this->buf.copy(b.buf);
	}
	void copy(const ALCharBuf& b) {
		this->buf.copy(b);
	}
	void copy(const char* b) {
		this->buf.copy(b);
	}

	ALString operator+(const ALString& s) {
		if (s.buf.ptr == nullptr && buf.ptr != nullptr) { return ALString(s.buf); }
		if (s.buf.ptr != nullptr && buf.ptr == nullptr) { return ALString(buf); }
		if (s.buf.ptr == nullptr && buf.ptr == nullptr) { return ALString(); }
		static ALString out(s.buf.size + buf.size + 1);
		out.zeroInit();
		out.buf.uinsert(buf);
		out.buf.uinsert(s.buf);
		return out;
	}
	ALString operator+(const char* s) {
		static ALString out(buf.size + strlen(s) + 1);
		out.zeroInit();
		out.buf.uinsert(buf);
		out.buf.uinsert(s);
		return out;
	}
	ALString operator+(const char& c) {
		static ALString out(buf.size + 2);
		out.zeroInit();
		out.buf.uinsert(buf);
		out.buf.uinsert(c);
		return out;
	}
	static ALString to_string(OStream& stream) {
		ALString out(stream.ptr);
		return out;
	}
	static ALString to_string(uint32_t num) {
		ALString out(11);
		out.zeroInit();
		
		uint32_t cnum = num;
		uint8_t i=0;
		for (; cnum != 0; i++) { cnum /= 10; };
		uint32_t temp  = i;
		while (num != 0) {
			out.buf.ptr[temp-1] = num % 10 + '0';
			temp--;
			num /= 10;
		}
		out.buf.size = i;
		return out;
	}

public:
	OStream next() {
		return buf.next();
	}
	void Serialize(IOBuffer& out) {
		buf.Serialize(out);
	}
	void Deserialize(IOBuffer& byteData) {
		buf.Deserialize(byteData);
	}
	char read() {
		return *(next().ptr);
	}
	uint16_t read16() {
		iterate_index += sizeof(uint16_t);
		return *(uint16_t*)(buf.ptr + iterate_index);
	}
	uint32_t read32() {
		iterate_index += sizeof(uint32_t);
		return *(uint32_t*)(buf.ptr + iterate_index);
	}
	uint64_t read64() {
		iterate_index += sizeof(uint64_t);
		return *(uint64_t*)(buf.ptr + iterate_index);
	}
	OStream readstream(uint64_t size) {
		OStream out(size);
		strcpy_s(out.ptr, size, buf.ptr);
		out.size = size;
		return out;
	}
	void write(char out) {
		buf.resize(iterate_index);
		buf.ptr[iterate_index] = out;
		iterate_index++;
	}
	void write16(uint16_t out) {
		buf.resize(iterate_index + sizeof(uint16_t));
		*((uint16_t*)(buf.ptr + iterate_index)) = out;
		iterate_index += sizeof(uint16_t);
	}
	void write32(uint32_t out) {
		buf.resize(iterate_index + sizeof(uint32_t));
		*((uint32_t*)(buf.ptr + iterate_index)) = out;
		iterate_index += sizeof(uint32_t);
	}
	void write64(uint64_t out) {
		buf.resize(iterate_index + sizeof(uint64_t));
		*((uint64_t*)(buf.ptr + iterate_index)) = out;
		iterate_index += sizeof(uint64_t);
	}
	void writestream(uint64_t size, char* data) {
		buf.resize(iterate_index+size);
		char* np = buf.ptr;
		strncpy_s(np,strlen(np), data, size);
		iterate_index += size;
	}
	void writestream(OStream stream) {
		writestream(stream.size, stream.ptr);
	}
	uint64_t hash() const {
		uint64_t result = 0;
		for (int i = 0; i < buf.size; i++) {
			result += buf.ptr[i];
		}
		result += buf.size;
		return result;
	}
	virtual char* getPrinted() {
		return buf.getPrinted();
	}
};




/*
* public:
    char* c_str;
public:
	ALString() {
		c_str = nullptr;
	}
	ALString(const char* b) {
		c_str = (char*)malloc(sizeof(b)+1);
		//printf("%s", c_str);
		strcpy_s(c_str, sizeof(c_str), b);
		assert(c_str != 0 && "Error: Error occured when copying from one string to another");
	}
	~ALString() {
		if (c_str != nullptr) {
			printf("%p\n", c_str);
			free(c_str);
		}
	}
public:

	size_t oplen() {
		return strlen(c_str);
	}
	ALString capitalize() {
		ALString a = c_str;
		for (int i = 0; i < strlen(c_str); i++) {
			if (c_str[i] >= 'a' && c_str[i] <= 'z') {
				//printf("C: %c, Code: %d,a: %d, z: %d\n", c_str[i],c_str[i],'a','z');
				a.c_str[i] = c_str[i] - 'a' + 'A';
			}
		}
		return a;
	}
	void reserve(unsigned int a) {
		if (c_str == nullptr) {
			c_str = (char*)malloc(a);
		}
		else {
			//assert(c_str != nullptr && "ERROR: Error when passing in c_str into realloc, check ram \\_(0-0)_/\n");
			char* tmp = (char*)realloc(c_str, a);
			if (tmp != nullptr) {
				c_str = tmp;
			}
			else {
				free(c_str);
				exit(1);
			}

		}
	}
public:
	void operator = (ALString val) {
		if (c_str == nullptr) {
			c_str = (char*)malloc(strlen(val.c_str));
		}
		else {
			c_str = (char*)realloc(c_str, strlen(val.c_str));
		}
		strcpy_s(c_str, sizeof(c_str), val.c_str);
	}
	void operator = (const char* b) {
		if (c_str == nullptr) {
			c_str = (char*)malloc(strlen(b));
		}
		else {
			c_str = (char*)realloc(c_str, strlen(b));
		}

		strcpy_s(c_str, sizeof(c_str), b);
	}
	ALString operator + (const char* b) {
		ALString out;
		out.reserve(strlen(c_str) + strlen(b)+1);
		for (int i = 0; i < strlen(c_str) + strlen(b)+1; i++) {
			if (i < strlen(c_str)) {
				out.c_str[i] = c_str[i];
				//printf("\tIn c_str: C: %c %d\n", c_str[i], c_str[i]);
			}
			else {
				//printf("\tIn b: C: %c %d\n", b[i- strlen(c_str)], b[i- strlen(c_str)]);
				out.c_str[i] = b[i-strlen(c_str)];
			}
			//printf("C: %c %d\n", out.c_str[i], out.c_str[i]);
		}
		return out;
	}
	ALString operator + (ALString b) {
		ALString out;
		out.reserve(strlen(c_str) + strlen(b.c_str) + 1);
		for (int i = 0; i < strlen(c_str) + strlen(b.c_str) + 1; i++) {
			if (i < strlen(c_str)) {
				out.c_str[i] = c_str[i];
			}
			else {
				out.c_str[i] = b.c_str[i - strlen(c_str)];
			}
		}
		return out;
	}
*/
//class ALString : public ALObj {
//public:
//	char* c_str;
//	size_t oplen() {
//		//printf(c_str);
//		//printf("Called oplen\n");
//		//printf("Hello, %u, %u", c_str, (int)(strlen(c_str)));
//		return (size_t)strlen(c_str);
//	}
//	ALString() {
//		c_str = nullptr;
//	}
//	template <unsigned int size>
//	ALString(const char* b) {
//		char arr[size + 1] = { 0 };
//		strcpy_s(arr, b);
//		c_str = arr;
//	}
//	ALString(char* b) {
//		c_str = (char*)malloc(strlen(b));
//	}
//	void capitalize() {
//		if (c_str != nullptr) {
//			for (int i = 0; i < this->oplen(); i++) {
//				if (c_str[i] >= 'a' && c_str[i] <= 'z') {
//					//printf("letter: %c",c_str[i]);
//					//printf("letter: %c", c_str[i]-32);
//					char b = c_str[i] - 32;
//					c_str[i] = b;
//				}
//			}
//		}
//	}
//
//};
