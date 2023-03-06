#pragma once
#include "../core/Exception.cpp"
#include <inttypes.h>
#include <string.h>
// TODO: fix __FILE__
#define MY_FILE_CURRENT (strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__)
class BasicException : public Exception{
private:
	void* functionPtr=nullptr;
	const char*  functionName;
	const char*  fileName;
	char* msg = nullptr;
	int data = 0;
	ExceptionType typ = BASIC_EXCEPTION;
public:
	BasicException(const char* n, const char* m, ExceptionType t=BASIC_EXCEPTION) : functionName(n), typ(t),
		fileName(MY_FILE_CURRENT)
	{
		uint64_t len = strlen(m);
		msg = new char[len + 1];
		strncpy_s(msg, len + 1, m, len);
	}
	BasicException(const char* n, const char* m, int _data, ExceptionType t=BASIC_EXCEPTION) : functionName(n), data(_data), typ(t),
		fileName(MY_FILE_CURRENT)
	{
		uint64_t len = strlen(m);
		msg = new char[len + 1];
		strncpy_s(msg, len + 1, m, len);
	}
	BasicException(const char* n, const char* m, void* function, ExceptionType t=BASIC_EXCEPTION) : functionName(n), typ(t),
		fileName(MY_FILE_CURRENT)
	{
		functionPtr = function;
		uint64_t len = strlen(m);
		msg = new char[len+1];
		strncpy_s(msg, len+1, m, len);
	}
	BasicException(const char* n, const char* m, void* function, int _data, ExceptionType t=BASIC_EXCEPTION) : functionName(n), data(_data),typ(t),
		fileName(MY_FILE_CURRENT)
	{
		functionPtr = function;
		uint64_t len = strlen(m);
		msg = new char[len + 1];
		strncpy_s(msg, len + 1, m, len);
	}
	~BasicException() {
		if(msg!=nullptr)        delete msg;
	}
public:
	virtual const char* getName() const {
		return functionName;
	}
	virtual const char* getMsg() const {
		return msg;
	}
	virtual void* getFunc() const {
		return functionPtr;
	}
	virtual const char* getFile() const {
		return fileName;
	}
	virtual ExceptionType getType() const {
		return typ;
	}
	virtual int getData() const {
		return data;
	}
};
