#pragma once
#include "../core/ALObj.cpp"
#include "../core/Iterateable.cpp"
#include "../core/Serializeable.cpp"
#include "ALLinkedListElement.cpp"
#include "../../utils/Helpers.cpp"
template <typename T>
class ALLinkedList : public Iterateable, public Serializeable{
private:
	ALLinkedListElement<T>* _first=nullptr;
	ALLinkedListElement<T>* _last=nullptr;
	uint64_t _size=0;
public:
	ALLinkedList() {
		_first = nullptr;
		_last = _first;
		_size = 0;
	}
	ALLinkedList(const ALLinkedList<T>& l) {
		ALLinkedListElement<T>* currentElement = l._first;
		ALLinkedListElement<T>* myLastElement = nullptr;
		ALLinkedListElement<T>* myCurrentPtr = l._first;
		//_first = l._first;
		_size = l._size;
		if (l._first != nullptr && l._first->self != nullptr) {
			_first = new ALLinkedListElement<T>();
			_first->self = new T(*l._first->self);
		}
		if (l._last != nullptr && l._last->self != nullptr) {
			_last = new ALLinkedListElement<T>();
			_last->self = new T(*l._last->self);
		}
		for (uint64_t i = 0; i < l._size; i++) {
			if (currentElement == nullptr) {
				this->_size = i;
				if (this->_last != nullptr) {
					delete _last;
				}
				this->_last = myLastElement;
				return;
			}
			myCurrentPtr = new ALLinkedListElement<T>;
			myCurrentPtr->self = new T(*currentElement->self);
			if (myLastElement != nullptr) {
				myLastElement->next = myCurrentPtr;
			}
			myLastElement = myCurrentPtr;
			currentElement = currentElement->next;
		}
	}
	~ALLinkedList() {
		ALLinkedListElement<T>* currentElement = _first;
		ALLinkedListElement<T>* nextElm = nullptr;
		for (uint64_t i = 0; i < _size; i++) {
			if (currentElement == nullptr) {
				ATLT::pushException(new BasicException(__FUNCTION__, "Nullptr element found in list that expects non-nullptr elements"));
				return;
			}

			nextElm = currentElement->next;
			delete currentElement;
			currentElement = nextElm;
		}
	}
public:
	uint64_t size() {
		return _size;
	}
	ALLinkedListElement<T>* first() {
		return _first;
	}
	ALLinkedListElement<T>* last() {
		return _last;
	}
	void insert(const T& element, const uint64_t& index=0) {
		if (index > _size) return;
		ALLinkedListElement<T>* n = new ALLinkedListElement<T>();
		n->self = new T(element);
		if (index == 0) {
			n->next = _first;
			_first = n;
			if (_size == 0) {
				_last = _first;
			}
			_size++;
			return;
		}
		if (index == _size) {
			if (_last == nullptr) { delete n; return; }
			//_last->next = n;
			_last->next = n;
			_last = n;
			_size++;
			return;
		}
		ALLinkedListElement<T>* currentElement = _first;
		ALLinkedListElement<T>* lastElement = nullptr;
		for (uint64_t i = 0; i < index; i++) {
			if (currentElement == nullptr) { 
				delete n; 
				ATLT::pushException(new BasicException(__FUNCTION__, "Found null element inside of a non-null accepting class\nThis could possibly be an error of some sort (currentElement==nullptr)"));
				return; 
			}
			lastElement = currentElement;
			currentElement = currentElement->next;
		}
		if (lastElement == nullptr) { 
			delete n; 
			ATLT::pushException(new BasicException(__FUNCTION__, "Found null element inside of a non-null accepting class\nThis could possibly be an error of some sort (lastElement==nullptr)")); 
			return;
		}
		n->next = currentElement;
		lastElement->next = n;
		_size++;
	}
	void push(const T& element) {
		insert(element, _size);
	}
	// TODO: Handle exceptions with an exception call stack...
	ALLinkedListElement<T> get(const uint64_t& index) {
		if (index == 0) {
			if (_first == nullptr) return ALLinkedListElement<T>();
			return *_first;
		}
		if (index == _size) {
			if (_last == nullptr) return ALLinkedListElement<T>();
			return *_last;
		}
		ALLinkedListElement<T>* currentElement = _first;
		for (uint64_t i=0; i < index; i++) {
			if (currentElement == nullptr) { return ALLinkedListElement<T>(); }
			currentElement = currentElement->next;
		}
		if (currentElement == nullptr) { return ALLinkedListElement<T>(); }
		return *currentElement;
	}
	void remove(const uint64_t& index) {
		ALLinkedListElement<T>* currentElement = _first;
		ALLinkedListElement<T>* lastElement = nullptr;
		for (uint64_t i = 0; i < index; i++) {
			if (currentElement == nullptr) { return; }
			lastElement = currentElement;
			currentElement = currentElement->next;
		}
		if (lastElement == nullptr) { return; }
		lastElement->next = currentElement->next;
		delete currentElement->self;
		_size--;
	}
public:
	virtual OStream next() {
		static ALLinkedListElement<T>* lastElementNext;
		if (lastElementNext == nullptr) lastElementNext = _first;
		if (lastElementNext == nullptr) return OStream();
		static OStream out(sizeof(ALLinkedListElement<T>));
		memcpy(out.ptr, lastElementNext,out.size);
		lastElementNext = lastElementNext->next;
		return out;
	}
	// TODO: Deserialializing of objects
	virtual void Deserialize(IOBuffer& byteData) {
		fprintf(stderr, "ERROR: Unimplemented");
		exit(1);
	/*	_size = byteData.read64();
		if (_first == nullptr) {
			_first = new ALLinkedListElement<T>;
		}
		ALLinkedListElement<T>* currentElement = _first;

		for (uint64_t i = 0; i < _size; i++) {
			
		}*/
	}
	virtual void Serialize(IOBuffer& out) {
		fprintf(stderr, "ERROR: Unimplemented");
		exit(1);
	}
};