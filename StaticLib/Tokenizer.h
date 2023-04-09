#pragma once
#include <iostream>
#include <fstream>
#include "string"


enum class TOKEN {  // все возможные типы данных при парсинге
	CURLY_OPEN,
	CURLY_CLOSE,
	COLON,
	STRING,
	COMMA
};


struct Token
{
	std::string value;  // значение токена
	TOKEN type;  // тип токена
	std::string getStringType() { // возращение типа в типе String. Нужно только для дэбага
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

class Tokenizer {  // анализатор файла
	std::fstream file;  // входной файл
public:
	Tokenizer(std::string filename);
	char getWithoutWhiteSpace();  // обрезаем пробелы и перенос строки

	Token getToken(); // поиск следующего токена в файле
	bool hasMoreTokens();  // проверяем на конец файла
};