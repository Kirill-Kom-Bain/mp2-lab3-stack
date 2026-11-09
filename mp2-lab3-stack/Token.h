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
	TokenType type = trash;
};
inline std::ostream& operator << (std::ostream& ostr, const Token& t) {
	if (t.type != trash) {
		ostr << t.Str;
	}
	return ostr;
	 }
