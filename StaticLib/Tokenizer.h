#pragma once
#include <iostream>
#include <fstream>
#include "string"


enum class TOKEN {
	CURLY_OPEN,
	CURLY_CLOSE,
	COLON,
	STRING,
	COMMA
};


struct Token
{
	std::string value;
	TOKEN type;
	std::string getStringType() {
		switch (type)
		{
		case TOKEN::CURLY_OPEN:
			return "CURLY_OPEN";
		case TOKEN::CURLY_CLOSE:
			return "CURLY_CLOSE";
		case TOKEN::COLON:
			return "COLON";
		case TOKEN::STRING:
			return "STRING";
		case TOKEN::COMMA:
			return "COMMA";
		default:
			return "ERROR";
		}
	}
};

class Tokenizer {
	std::fstream file;
	int prevPos;
public:
	Tokenizer(std::string filename);
	char getWithoutWhiteSpace();

	Token getToken();
	bool hasMoreTokens();
};