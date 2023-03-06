#pragma once
#include <inttypes.h>
enum ExceptionType {
	NONE = 0,
	CPP_EXCEPTION,
	BASIC_EXCEPTION
};
class Exception {
public:
	virtual const char*			  getName() const = 0;
	virtual const char*			  getMsg()  const = 0;
	virtual const char*			  getFile() const = 0;
 	virtual void*				  getFunc() const = 0;
	virtual ExceptionType         getType() const {return NONE;}
	virtual int                   getData() const {return -1;  }
	virtual char*                 getContext() const { return nullptr; }
};