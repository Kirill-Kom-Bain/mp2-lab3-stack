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

};