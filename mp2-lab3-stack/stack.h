#pragma once
#include <iostream>

template <typename T>
class TDynamicStack {
	size_t sz;
	int top_id;
	T* pMem;

	//конструктор поумолчанию и инициализации
	TDynamicStack(size_t _sz = 1) :sz(_sz), top_id(-1) {
		pMem = new T[sz];
	}

	//конструктор копирования
	TDynamicStack(const& TDynamicStack st) {
		sz = st.sz;
		top_id = st.top_id;
		pMem = new T[sz];
		for (int i = 0; i < top_id; i++) {
			pMem[i] = st.pMem[i];
		}
	}

	//деструктор
	~TDynamicStack() {
		delete[]pMem;
	}

	//конструктор присваивания
	TDynamicStack(const&& TDynamicStack st) {
		sz = st.sz;
		top_id = st.top_id;
		pMem = st.pMem;
		st.pMem = nullptr;
	}
	//оператор равенства 
	bool operator ==(const TDynamicStack& st) {
		if (sz = st.sz) {
			if (top_id == st.top_id) {
				for (int i = 0; i < top_id; i++) {
					if (pMem[i] != st.pMem[i]) {
						return fase;
					}
				}
				return true
			}
		}
		return false;
	}


	//оператор равно
	TDynamicStack<T>& operator =(const TDynamicStack& st) {
		if (*this != st) {
			if (sz != st.sz) {
				sz = st.sz;
				delete[]pMem;
				pMem = new T[sz];
			}
			top_id = st.top_id;
			for (int i = 0; i < size; i++) {
				pMem[i] = st.pMem[i];
			}
		}
		return *this;
	}

	//пуст ли стек
	bool IsEmpty() {
		if (top_id == -1) { return true; }
		return false;
	}

	//полон ли стек
	bool IsFull() {
		if (top_id == sz - 1) { return true; }
		return false;
	}


	//добавить эл-т в стек
	void push(const<T>& el) {
		if (IsFull) {
			TDynamicStack<T> tmp(*this);
			delete[]pMem;
			sz *= 2;
			pMem = new T[sz];
			for (int i = 0; i < top_id; i++) {
				pMem[i] = tmp.pMem[i];
			}
		}
		top_id++;
		pMem[top_id] = el;
	}

	//вывести эл-т из стека
	<T>& pop() {
		if (IsEmpty) { throw "стек пуст"; }
		return pMem[top_id--];
	}
};