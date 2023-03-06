#include "../../core/ALObj.cpp"
#include "../../core/IOBuffer.cpp"
#include "../ALString.cpp"
class ALFile : public ALObj, public IOBuffer
{
public:
	ALString path;
private:
	FILE* file;
public:
	ALFile(const char* path, const char* mode) : path(path) {
		fopen_s(&file, path, mode);
	}
	ALFile(ALString& path, const char* mode) : path(path) {
		fopen_s(&file, path.c_str(), mode);
	}
	~ALFile() { fclose(file); }
public:
	FILE* get_raw() { return file; }
	void close() { fclose(file); }
	void open(const char* path, const char* mode) {
		this->path = path;
		fopen_s(&file, path, mode);
	}
public:

	void write(char out) {
		fwrite(&out, 1, 1, file);
	}
	void write16(uint16_t out) {
		fwrite(&out, sizeof(uint16_t), 1, file);
	}
	void write32(uint32_t out) {
		fwrite(&out, sizeof(uint32_t), 1, file);
	}
	void write64(uint64_t out) {
		fwrite(&out, sizeof(uint64_t), 1, file);
	}
	void writestream(uint64_t size, char* data) {
		fwrite(data, size, 1, file);
	}
	void writestream(OStream stream) {
		writestream(stream.size, stream.ptr);
	}

	char read() {
		char o = 0;fread(&o, 1, 1, file);
		return o;
	}
	uint16_t read16() {
		uint16_t o = 0; fread(&o, sizeof(uint16_t), 1, file);
		return o;
	}
	uint32_t read32() {
		uint32_t o = 0; fread(&o, sizeof(uint32_t), 1, file);
		return o;
	}
	uint64_t read64() {
		uint64_t o = 0; fread(&o, sizeof(uint64_t), 1, file);
		return o;
	}
	OStream readstream(uint64_t size) {
		OStream out(size + 1);
		out.zeroInit();
		fread(out.ptr, size, 1, file);
		out.size = size;
		return out;
	}
};
