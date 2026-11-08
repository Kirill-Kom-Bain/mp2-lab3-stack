#include "stack.h"
#include"Calculator.h"
#include"Token.h"
#include"Cont.h"
#include <locale.h>
#include<iostream>

int main() {
	setlocale(LC_ALL, "rus");
	std::setlocale(LC_NUMERIC, "C");//читать . как начало дробной части у числа при русской локализации
	std::cout << "is_started\n";
	Calculator a("3.5+4.2*(2-1)");
	std::cout << a.infix.length()<<"\n";
	a.infix_to_cont();
	std::cout << a.get_inf_cont();
	std::cout << "is_ended";


}