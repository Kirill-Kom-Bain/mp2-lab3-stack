#pragma once
#include"Token.h"
#include <iostream>
#include <string.h>
#include "Cont.h"



class Calculator {
	public:
	std::string infix, postfix;
	Container<Token> inf_cont, post_cont;
public:
	Calculator(std::string _infix):infix(_infix),postfix("") {
		inf_cont.clear();
		post_cont.clear();
	}
	Container<Token>& get_inf_cont() {
		return inf_cont;
	}
	Container<Token>& get_post_cont() {
		return post_cont;
	}
	//парс инфиксной строки
	void infix_to_cont() {
		inf_cont.resize(infix.length());
		int i = 0;
		while (i < infix.length()) {
			Token t;
			if (infix[i] == '(') {
				t.type = opBr;
				t.Str = '(';
				inf_cont.push_back(t);
				i++;

			}
			else if (infix[i] == ')') {
				t.type = clBr;
				t.Str = ')';
				inf_cont.push_back(t);
				i++;
			}
			else if (infix[i] == '+') {
				t.type = operation;
				t.Str = '+';
				inf_cont.push_back(t);
				i++;
			}
			else if (infix[i] == '-') {
				t.type = operation;
				t.Str = '-';
				inf_cont.push_back(t);
				i++;
			}
			else if (infix[i] == '*') {
				t.type = operation;
				t.Str = '*';
				inf_cont.push_back(t);
				i++;
			}
			else if (infix[i] == '/') {
				t.type = operation;
				t.Str = '/';
				inf_cont.push_back(t);
				i++;
			}
			else if ((infix[i] >= '0' && infix[i] <= '9') || infix[i] == '.') {
				char* p;
				t.type = number;
				t.Val = strtod(&infix[i], &p);
				int delta = p - &infix[i];
				t.Str = infix.substr(i, delta);
				i += delta;
				inf_cont.push_back(t);
			}
			else {
				i++;
			}
		}
		
	}

	void infix_cont_to_postfix_cont() {
		TDynamicStack<Token>operation_stack;
		//post_cont.resize(inf_cont.getsize());
		for (int i = 0; i < inf_cont.getsize(); i++) {
			//если число, то сразу кладем в стек
			if (inf_cont[i].type == number) {
				post_cont.push_back(inf_cont[i]);
			}
			//если не число то либо скобки либо операции
			// 
			//если операция то проверяем пуст ли стек, если стек пуст кладем операцию в стек, если в стеке есть операция,
			// сравниваем их, если операция в стеке равносильная или сильнее, то выносим ее в контейнер, а новую операцию кладем в стек
			if (inf_cont[i].type == operation) {
				
				// случаи для сравнения 
				// 
				// 1 если у нас + или - мы всегда переносим в цикле операции стека
				// все кроме ( значит цикл while пока стек не пуст или не (
				if (inf_cont[i].Str == "+" || inf_cont[i].Str == "-") {
					while (!(operation_stack.IsEmpty()) && operation_stack.top().Str != "(") {
						post_cont.push_back(operation_stack.pop());
					}
				}
				// 2 если у нас * или / мы переносим в цикле операции стека 
				// пока не встретим ( или + или -
				if (inf_cont[i].Str == "*" || inf_cont[i].Str == "/") {
					while (!(operation_stack.IsEmpty()) && (operation_stack.top().Str == "*" || operation_stack.top().Str == "/" )) {
						post_cont.push_back(operation_stack.pop());
					}
				}
				operation_stack.push(inf_cont[i]);
			}
			//если ( то кладем ее в стек
			if (inf_cont[i].type == opBr) {
				operation_stack.push(inf_cont[i]);
			}
			//если ) то переносим в контейнер все операции до ( а саму ( удаляем из стека
			if (inf_cont[i].type == clBr) {
				while (!operation_stack.IsEmpty() && operation_stack.top().Str != "(") {
					post_cont.push_back(operation_stack.pop());
					//if (operation_stack.top().Str == "") { operation_stack.pop();}
					/*Token a = operation_stack.pop();
					post_cont.push_back(a);
					post_cont.push_back(a);
					*/
				}
				if (!operation_stack.IsEmpty() && operation_stack.top().Str == "(") {
					operation_stack.pop();
				}
				else{
					throw "ERR неверный ввод операций, есть закрытая скобка, но нет открытой";
				}
			}
		}
		//когда прошлись по всем операциям, пока стек не пуст переносим все операции в контейнер
		while (!operation_stack.IsEmpty()) {
			Token op = operation_stack.pop();
			if (op.type == operation && op.Str!="") {
				post_cont.push_back(op);
			}
		}
		
		//отловить лишние пробелы 
		//вывод
		/* 3.5
		4.2
		2
		1
		-
		*
		+
		3.5 4.2 2 1 - ' ' ' ' * + ' '
		*/
		for (int i = 0; i < post_cont.getsize(); i++) {
			if (post_cont[i].Str != "") {
			std::cout << post_cont[i] << "\n";
		}
			
			if (post_cont[i].Str == ""){//&& post_cont[i + 1].Str == " ") {
				post_cont[i].Str = "'";
			}
			
		}
	}
	// почему-то выводится - (5 пробелов) * +
	// откуда берутся пробелы???
	//

};