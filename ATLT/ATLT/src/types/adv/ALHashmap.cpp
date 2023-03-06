#pragma once
#include "ALHashkey.cpp"
#include "../basic/ALString.cpp"
#include "Hashable.cpp"
#include "../basic/ALList.cpp"
#include "../basic/ALLinkedList.cpp"
#include "../basic/ALUint64.cpp"
#include <type_traits>
template<typename Hash, typename T>
class ALHashmap {
	static_assert(std::is_base_of<Hashable, Hash>::value, "Error: from hash must be a Hashable!");
public:
	ALList<ALHashkey<Hash, T>> _map;
	ALHashmap(uint64_t size) : _map(size) {};
	ALList<ALHashkey<Hash, T>> map() {
		return _map;
	}
	uint64_t hashToIndex(const Hash& key) {
		if (!_map.getCount()) { fprintf(stderr, "ERROR: Amount of elements in hash is less than 1!"); exit(1); }
		return key.hash() % _map.getCount();
	}
	ALLinkedList<T> get(const Hash& key) {
		return _map.get(hashToIndex(key)).values;
	}
	void push(const Hash& key, const T& value) {
		_map.get(hashToIndex(key)).values.push(value);
	}
};
//template<typename T>
//class ALHashmap {
//private:
//	ALList<ALHashkey<T>> map;
//public:
//	ALHashmap(uint64_t size) : map(size) {};
//	ALList<ALHashkey<T>> getRaw() {
//		return map;
//	}
//	uint64_t hashToIndex(const uint64_t& key) {
//		return key % map.getCount();
//
//	}
//	ALLinkedList<T> get(const uint64_t& key) {
//		return map.get(hashToIndex(key)).values;
//	}
//	ALLinkedList<T> get(Hashable& key) {
//		return map.get(hashToIndex(key.hash())).values;
//	}
//	void push(const uint64_t& key, const T& value) {
//		map.get(hashToIndex(key)).values.insert(value);
//	}
//	
//
//}



//template<Identifier -> String | ID, Value>


//
//template<typename T>
//class ALHashmap {
//private:
//	ALList<ALHashkey<T>> map;
//public:
//	ALHashmap() {};
//	ALList<ALHashkey<T>> getRaw() {
//		return map;
//	}
//	T get(Hashable& key) {
//		return map.get(key.hash() % (uint64_t)map.getCount()).value;
//	}
//	T get(Hashable&& key) {
//		return map.get(key.hash() % (uint64_t)map.getCount()).value;
//	}
//
//	T get(uint64_t key){
//		return map.get(key % (uint64_t)map.getCount()).value;
//	}
//	ALHashkey<T> getElement(uint64_t key) {
//		return map.get(key % (uint64_t)map.getCount());
//	}
//	ALHashkey<T> getElement(Hashable& key) {
//		return map.get(key.hash() % (uint64_t)map.getCount());
//	}
//	void resize(uint32_t count) {
//		map.resize(count);
//	}
//	//bool push(Hashable& key, T value) {
//	//	ALListElement<ALHashkey<T>> element = this->getElement(key);
//	//	if (element.empty) {
//	//		map.set(key.hash(), ALHashkey<T>(key.hash(), value));
//	//		return true;
//	//	}
//	//	else {
//	//		return false;
//	//	//	map.resize(map.getCount() + 1);
//	//	}
//	//}
//	//bool push(Hashable&& key, T value) {
//	//	ALListElement<ALHashkey<T>> element = this->getElement(key);
//	//	if (element.empty) {
//	//		map.set(key.hash(), ALHashkey<T>(key.hash(), value));
//	//		return true;
//	//	}
//	//	else {
//	//		return false;
//	//		//	map.resize(map.getCount() + 1);
//	//	}
//	//}
//};