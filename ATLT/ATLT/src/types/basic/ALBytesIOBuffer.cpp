#pragma once
#include "../core/IOBuffer.cpp"
#include "../../utils/Helpers.cpp"
#include "string.h"
class ALBytesIOBuffer : public IOBuffer{
private:
	char* data;
	uint64_t size;
	uint64_t max_size;
	uint64_t iter_index = 0;
public:
	static const uint32_t skip = 500;
public:
	ALBytesIOBuffer() {
		size = 0;
		max_size = 0;
		data = (char*)malloc(1);
	}
	ALBytesIOBuffer(uint64_t size) {
		this->size = size;
		this->max_size = (size/skip+1)*skip;
		this->data = (char*)malloc(max_size);
	}
	~ALBytesIOBuffer() {
		free(data);
	}
	void resize(uint64_t _size) {
		void* temp = realloc(data, (_size / skip + 1) * skip);
		if (temp == nullptr) { free(data); ATLT::pushException(new BasicException(__FUNCTION__, "Could not reallocate the buffer, probably because you ran out of ram", CPP_EXCEPTION));return;}
		data = (char*)temp;
	}
	char* getRaw()                   { return data; }
	uint64_t getSize()               { return size; }
	uint64_t getMaxSize()            { return max_size; }
	uint64_t getIterindex()          { return iter_index; }
	void setIterindex(uint64_t iter) { iter <= max_size ? iter_index = iter : 0; }
public:
	void write(char out) {
		if (size + 1 > max_size) {
			void* temp = realloc(data, max_size + skip);
			if (temp == nullptr) {
				free(data);
				ATLT::pushException(new BasicException(__FUNCTION__, "Could not reallocate the buffer, probably because you ran out of ram",CPP_EXCEPTION));
				return;
			}
			data = (char*)temp;
			data[size] = out;
			size++;
			return;
		}
		data[size] = out;
		size++;
	}
	void write16(uint16_t out) {
		if (size + sizeof(out) > max_size) {
			void* temp = realloc(data, max_size + skip);
			if (temp == nullptr) {
				free(data); 
				ATLT::pushException(new BasicException(__FUNCTION__, "Could not reallocate the buffer, probably because you ran out of ram", CPP_EXCEPTION));
				return;
			}
			data = (char*)temp;
			*((uint16_t*)(data+size)) = out;
			size += sizeof(out);
			return;
		}
		*((uint16_t*)(data + size)) = out;
		size+=sizeof(out);
	}
	void write32(uint32_t out) {
		if (size + sizeof(out) > max_size) {
			void* temp = realloc(data, max_size + skip);
			if (temp == nullptr) { free(data); ATLT::pushException(new BasicException(__FUNCTION__, "Could not reallocate the buffer, probably because you ran out of ram", CPP_EXCEPTION));
			return;
			}
			data = (char*)temp;
			*((uint32_t*)(data + size)) = out;
			size += sizeof(out);
			return;
		}
		*((uint32_t*)(data + size)) = out;
		size += sizeof(out);
	}
	void write64(uint64_t out) {
		if (size + sizeof(out) > max_size) {
			void* temp = realloc(data, max_size + skip);
			if (temp == nullptr) { free(data); ATLT::pushException(new BasicException(__FUNCTION__, "Could not reallocate the buffer, probably because you ran out of ram", CPP_EXCEPTION));
			return;
			}
			data = (char*)temp;
			*((uint64_t*)(data + size)) = out;
			size += sizeof(out);
			return;
		}
		*((uint64_t*)(data + size)) = out;
		size += sizeof(out);
	}
	void writestream(uint64_t nsize, char* data) {
		if ((size + nsize) > max_size) {
			uint64_t nskip = (nsize/skip + 1)*skip;
			void* temp = realloc(data, max_size + nskip);
			if (temp == nullptr) { free(data); ATLT::pushException(new BasicException(__FUNCTION__, "Could not reallocate the buffer, probably because you ran out of ram", CPP_EXCEPTION));return;}
			data = (char*)temp;
			//*((uint64_t*)(data + size)) = ;
			strcpy_s(data + nsize, nsize, data);
			//strcpy_s((data+nsize))
			size += sizeof(nsize);
			return;
		}
		strcpy_s(data + nsize, nsize, data);
		size += nsize;
	}
	void writestream(OStream stream) {
		writestream(stream.size, stream.ptr);
	}
	char read() {
		char out = data[iter_index];
		iter_index++;
	}
	uint16_t read16() {
		
		uint16_t out =  *((uint16_t*)(data + iter_index));
		iter_index += sizeof(uint16_t);
	}
	uint32_t read32() {
		uint32_t out = *((uint32_t*)(data + iter_index));
		iter_index += sizeof(uint32_t);
	}
	uint64_t read64() {
		uint64_t out = *((uint64_t*)(data + iter_index));
		iter_index += sizeof(uint64_t);
	}
	OStream readstream(uint64_t _size) {
		OStream out(size);out.zeroInit();
		if (iter_index + _size > max_size) return out;
		strcpy_s(out.ptr, _size, data+iter_index);
		iter_index += _size;
		return out;
	}
};