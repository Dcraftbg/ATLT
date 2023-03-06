#pragma once
#include "Exception.cpp"
#include "../basic/ALStackPtr.cpp"
#include "../basic/BasicException.cpp"
#include <memory>
class ExceptionStack {
public:
	virtual bool push(Exception* except) = 0;
	virtual Exception* last() = 0;
	virtual std::unique_ptr<Exception> pop() = 0;
};