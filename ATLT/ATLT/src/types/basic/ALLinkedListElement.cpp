#pragma once
template <typename T>
class ALLinkedListElement {
public:
	T* self=nullptr;
	ALLinkedListElement<T>* next=nullptr;
public:
	ALLinkedListElement() {}
	ALLinkedListElement(const ALLinkedListElement<T>& l) {
		// This is very dangerous since we are literally copying the entirety of the rest of the table, so you should instead return a reference not this you dum dum
		if (l.self != nullptr) {
			this->self = new T(*l.self);
		}
		if (l.next != nullptr) {
			this->next = new ALLinkedListElement<T>(*l.next);
		}
	}
	~ALLinkedListElement() {
		if(self!=nullptr) delete self;
	}
};