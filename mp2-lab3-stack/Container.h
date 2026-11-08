#pragma once
#include <iostream>

template <typename T> class Container;

template <typename T>
std::ostream& operator << (std::ostream& os, const Container<T>& el);

template <typename T>
std::istream& operator >> (std::istream& is, Container<T>& el);

template<typename T>
class Container {
	int size;
	T* pMem;
public:
	//–еализовать:
	//конструктор по умолчанию
	// деструктор
	// конструктор иниц
	// конструктор копировани€
	// конструктор перемещени€
	// переопределить оператор = (с проверкой на самокопирование)
	// переопределить оператор присваивани€ с перемещением (передаем объект по r-value)
	// переопределить оператор индексации
	// переопределить ввод вывод 
	// реализовать метод resize дл€ задани€ нового размера
	//
	Container() :size(0), pMem(nullptr) {}

	~Container() {
		if (pMem) { delete[]  pMem; }
	}

	Container(int _size) : size(_size) {
		pMem = new T[size];
	}

	Container(const Container& el) {
		size = el.size;
		pMem = new T[size];
		for (int i = 0; i < size; i++) {
			pMem[i] = el.pMem[i];
		}
	}

	Container(Container&& el) {
		size = el.size;
		el.size = 0;
		pMem = el.pMem;
		el.pMem = nullptr;
	}

	Container& operator = (const Container& el);

	Container& operator = (Container&& el);

	T& operator[] (int index);

	friend std::istream& operator >> <T>( std::istream& is , Container& el );

	friend std::ostream& operator << <T>( std::ostream& os , const Container& el );

	Container& resize(int _size) {
		if (size < _size) {
			T* tmp;
			tmp = new T[_size];
			std::cout << "–азмер будет увеличен,предыдущие элементы останутс€\n ";
			for (int i = 0; i < size; i++) {
				tmp[i] = pMem[i];
			}
			for (int i = size; i < _size; i++) {
				tmp[i] = 0;
			}
			delete[]pMem;
			pMem = tmp;
			size = _size;
		}
		if (size > _size) {
			T* tmp;
			tmp = new T[_size];
			std::cout << "–азмер будет уменьшен,предыдущие элементы будут частично сохранены\n ";
			size = _size;
			for (int i = 0; i < _size; i++) {
				tmp[i] = pMem[i];
			}
			delete[]pMem;
			pMem = tmp;
		}
		return *this;
	}

};

template <typename T>
std::ostream& operator << (std::ostream& os, const Container<T>& el) {
	os << "size " << el.size << "\n";
	for (int i = 0; i < el.size; i++) {
		os << el.pMem[i] <<" ";
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

template<typename T>
T& Container<T>:: operator[] (int index) {
	return pMem[index];
}

template<typename T>
Container<T>& Container<T>:: operator =(const Container& el) {
	if (this != &el) {
		if (size != el.size) {
			delete[]pMem;
			size = el.size;
			pMem = new T[size];
		}
		for (int i = 0; i < size; i++){
			pMem[i] = el.pMem[i];
		}
	}
	return *this;
}

template <typename T>
Container<T>& Container<T>:: operator = ( Container&& el) {
	if (this != &el) {
		size = el.size;		
		el.size = 0;
		delete [] pMem;
		pMem = el.pMem;
		el.pMem = nullptr;
	}
	return *this;
}