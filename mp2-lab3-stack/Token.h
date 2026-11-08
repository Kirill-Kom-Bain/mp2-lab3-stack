#pragma once
#include <iostream>
#include <string.h>

enum TokenType {
	number,
	operation,
	opBr,
	clBr
};

struct Token {
	std::string Str;
	double Val;
	TokenType type;
};
inline std::ostream& operator << (std::ostream& ostr, const Token& t) {
	ostr << t.Str;
	return ostr;
	 }
