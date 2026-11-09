#pragma once
#include <iostream>
#include <string.h>

enum TokenType {
	trash,
	number,
	operation,
	opBr,
	clBr
};

struct Token {
	std::string Str ="";
	double Val;
	int Prioryty = 0;
	TokenType type = trash;
};
std::ostream& operator << (std::ostream& ostr, const Token& t) {
	if (t.type != trash) {
		ostr << t.Str;
	}
	return ostr;
	 }
