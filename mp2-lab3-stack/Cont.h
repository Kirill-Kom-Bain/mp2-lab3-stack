#pragma once
#include <iostream>

template <typename T>
class Container;
template <typename T>
std::ostream& operator << (std::ostream& os, const Container<T>& el);

template <typename T>
std::istream& operator >> (std::istream& is, Container<T>& el);

template<typename T>
class Container {
	int size, top_id;
	T* pMem;

public:
	Container() : size(0), top_id(0), pMem(nullptr) {}

	~Container() {
		if (pMem) { delete[] pMem; }
	}

	Container(int _size) : size(_size), top_id(0) {
		pMem = new T[size];
	}

	Container(const Container& el) {
		size = el.size;
		top_id = el.top_id;
		pMem = new T[size];
		for (int i = 0; i < size; i++) {
			pMem[i] = el.pMem[i];
		}
	}

	Container(Container&& el) noexcept {
		size = el.size;
		top_id = el.top_id;
		pMem = el.pMem;
		el.size = 0;
		el.top_id = 0;
		el.pMem = nullptr;
	}

	Container& operator = (const Container& el) {
		if (this != &el) {
			if (size != el.size) {
				delete[] pMem;
				size = el.size;
				pMem = new T[size];
			}
			top_id = el.top_id;
			for (int i = 0; i < size; i++) {
				pMem[i] = el.pMem[i];
			}
		}
		return *this;
	}

	Container& operator = (Container&& el) noexcept {
		if (this != &el) {
			delete[] pMem;
			size = el.size;
			top_id = el.top_id;
			pMem = el.pMem;
			el.size = 0;
			el.top_id = 0;
			el.pMem = nullptr;
		}
		return *this;
	}

	T& operator[] (int index) {
		return pMem[index];
	}

	const T& operator[] (int index) const {
		return pMem[index];
	}

	friend std::istream& operator >> <T>(std::istream& is, Container& el);
	friend std::ostream& operator << <T>(std::ostream& os, const Container& el);

	Container& resize(int _size) {
		if (size < _size) {
			T* tmp = new T[_size];
			for (int i = 0; i < size; i++) {
				tmp[i] = pMem[i];
			}
			for (int i = size; i < _size; i++) {
				tmp[i] = T();
			}
			delete[] pMem;
			pMem = tmp;
			size = _size;
		}
		else if (size > _size) {
			T* tmp = new T[_size];
			size = _size;
			if (top_id > size) {
				top_id = size;
			}
			for (int i = 0; i < _size; i++) {
				tmp[i] = pMem[i];
			}
			delete[] pMem;
			pMem = tmp;
		}
		return *this;
	}

	void push_back(T el) {
		if (size == 0) {
			size = 1;
			pMem = new T[size];
			top_id = 0;
		}
		if (top_id >= size) {
			Container<T> tmp(*this);
			size = size * 2;
			delete[] pMem;
			pMem = new T[size];
			for (int i = 0; i < top_id; i++) {
				pMem[i] = tmp.pMem[i];
			}
		}
		pMem[top_id] = el;
		top_id++;
	}

	void clear() {
		delete[] pMem;
		pMem = nullptr;
		size = 0;
		top_id = 0;
	}
};


template <typename T>
std::ostream& operator << (std::ostream& os, const Container<T>& el) {
	os << "size " << el.size << "\n";
	for (int i = 0; i < el.size; i++) {
		os << el.pMem[i] << " ";
	}
	os << "\n";
	return os;
}

template <typename T>
std::istream& operator >> (std::istream& is, Container<T>& el) {
	std::cout << "input size ";
	is >> el.size;
	el.resize(el.size);
	for (int i = 0; i < el.size; i++) {
		std::cout << "input " << i << " el\n";
		is >> el.pMem[i];
	}
	return is;
}