#pragma once
template <typename T>
class ALStackPtr {
private:
	T* ptr;
public:
	ALStackPtr(T* p) {
		ptr = p;
	}
	T& operator*() const {
		return *ptr;
	}
	T* operator->() const {
		return ptr;
	}
	operator T* () const {
		return ptr;
	}
	~ALStackPtr() {
		delete ptr;
	}
};