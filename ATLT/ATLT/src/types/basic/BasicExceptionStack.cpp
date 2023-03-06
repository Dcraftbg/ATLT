#pragma once
#include "../core/ExceptionStack.cpp"
#include "../../utils/Helpers.cpp"
#include "ALArray.cpp"
#include <inttypes.h>
#include "ALStackPtr.cpp"
template <uint64_t max_size=20>
class BasicExceptionStack : public ExceptionStack {
private:
	
	ALArray<Exception*,max_size> stack;
public:
	BasicExceptionStack() {}
	~BasicExceptionStack() {
		#ifdef _LEFTOVER_EXCEPTION_WARN
		if (stack.getSize()) {
			fprintf(stdout, "Warning: Unhandled data on the BasicExceptionStack (%p)", this);
		}
		#endif
		for (uint64_t i = 0; i < stack.getSize(); i++) {
			#ifdef _PRINT_LEFTOVER_EXCEPTION_STACK
				ATLT::HandleExceptionOn(ATLT::HandleBasicException, this);
			#else
			if (stack.get(i) != nullptr) {
				delete stack.get(i);
			}
			#endif		
		}
	}
	virtual bool push(Exception* except) {
		return stack.push(except);
	}
	virtual Exception* last() {
		return stack.get(stack.getSize() - 1);
	}
	virtual std::unique_ptr<Exception> pop() {
//		delete stack.get(stack.getSize());
		return std::unique_ptr<Exception>(stack.pop());
	}
};
