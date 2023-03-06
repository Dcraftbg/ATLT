#pragma once
#include "../types/core/Printable.cpp"
#include "../types/core/ExceptionStack.cpp"
#include <stdio.h>
#include <inttypes.h>
#include <stdlib.h>
#define MAY_THROW_EXCEPTION
namespace ATLT {
	std::unique_ptr<ExceptionStack> exception_stack=nullptr;
	void HandleException(void (*func)(std::unique_ptr<Exception>));
	void HandleExceptionOn(void (*func)(std::unique_ptr<Exception>), ExceptionStack* stack);
	void HandleBasicException(std::unique_ptr<Exception>);
	void HandleIfPop(bool (*func)(Exception*));
	void HandleIfPopOn(bool (*func)(Exception*), ExceptionStack* stack);
	void pushException(Exception* p);
	void Print(Printable& p);
	void Print(int p);
	void Print(uint32_t p);
	void Print(uint64_t p);
	void Print();
	void Print(const char* p);
	void Print(char p);
	void Print(void* p);
	void Print(bool p);

	void PrintL(Printable& p);
	void PrintL(int p);
	void PrintL(uint32_t p);
	void PrintL(uint64_t p);
	void PrintL();
	void PrintL(const char* p);
	void PrintL(char p);
	void PrintL(void* p);
	void PrintL(bool p);
	
}
void ATLT::Print(Printable& p) { printf(p.getPrinted()); }
void ATLT::Print(int p) { printf("%d", p); }
void ATLT::Print(uint32_t p) { printf("%u", p); }
void ATLT::Print(uint64_t p) { printf("%llu", p); }
void ATLT::Print() { fputc('\n', stdout); }
void ATLT::Print(const char* p) { printf(p); }
void ATLT::Print(char p) { printf("%c", p); }
void ATLT::Print(void* p) { printf("%p", p); }
void ATLT::Print(bool p) {
	if (p) { printf("true"); return; }
	printf("false"); return;
}

void ATLT::PrintL(Printable& p) { printf("%s\n", p.getPrinted()); }
void ATLT::PrintL(int p) { printf("%d\n", p); }
void ATLT::PrintL(uint32_t p) { printf("%u\n", p); }
void ATLT::PrintL(uint64_t p) { printf("%llu\n", p); }
void ATLT::PrintL() { fputc('\n', stdout); }
void ATLT::PrintL(const char* p) { printf("%s\n", p); }
void ATLT::PrintL(char p) { printf("%c\n", p); }
void ATLT::PrintL(void* p) { printf("%p\n", p); }
void ATLT::PrintL(bool p) { if (p) { printf("true\n"); return; }printf("false\n"); return; }
void ATLT::pushException(Exception* p) {
	if (exception_stack == nullptr) {
		fprintf(stderr, "ERROR: poor exception_stack handling.\nException stack either got replaced or was never set in the first place"); exit(1); return;
	}	if (exception_stack->push(p)) {
		fprintf(stderr, "ERROR: poor exception_stack handling.\nException stack has unhandled exceptions and has filled up!"); exit(1); return;
	}
}
void ATLT::HandleException(void (*func)(std::unique_ptr<Exception>)) {
	func(ATLT::exception_stack->pop());
}

void ATLT::HandleExceptionOn(void (*func)(std::unique_ptr<Exception>),ExceptionStack* stack) {
	func(stack->pop());
}

void ATLT::HandleBasicException(std::unique_ptr<Exception> e) {
	/*ATLT::Print("Error: ");
	ATLT::Print(e->getType());
	ATLT::Print(' ');
	ATLT::Print("(");
	ATLT::Print(e->getName());
	ATLT::Print(": ");
	ATLT::Print(e->getFunc());
	ATLT::Print(")");
	ATLT::Print(" - ");
	ATLT::Print(e->getData());
	ATLT::Print(" ");
	ATLT::PrintL(e->getMsg());*/
	if (e == nullptr) return;
	printf("Error: %d (%s: %p) - %d %s\n", e->getType(), e->getName(), e->getFunc(), e->getData(), e->getMsg());
	/*ATLT::Print("Error: at ");
	ATLT::Print(e->getFunc());
	ATLT::Print(" with name ");
	ATLT::Print(e->getName());
	ATLT::Print(" in: ");
	ATLT::Print(e->getFile());
	ATLT::PrintL(":");
	ATLT::PrintL(e->getMsg());*/
}
void ATLT::HandleIfPop(bool (*func)(Exception*)){
	func(ATLT::exception_stack->last()) ? ATLT::exception_stack->pop() : 0;
}
void ATLT::HandleIfPopOn(bool (*func)(Exception*), ExceptionStack* stack) {
	func(stack->last()) ? stack->pop() : 0;
}

