#include "Tokenizer.h"


Tokenizer::Tokenizer(const std::string filename){
	file.open(filename, std::ios::in);
	if (!file.good()) {  // проверка, что файл удалось отрыть
		std::cout << "File open error" << std::endl;
	}
}

char Tokenizer::getWithoutWhiteSpace() {
	char c = ' ';
	while ((c == ' ' || c == '\n'))
	{
		file.get(c); // check

		if ((c == ' ' || c == '\n') && !file.good())
		{
			// если самый конец файла, то вернем пустую строку
			//std::cout << file.eof() << " " << file.fail() << std::endl;
			return ' ';
		}
		else if (!file.good())
		{
			return c;
		}
	}
	// std::cout << "NOWHITE: " << c << std::endl;
	return c;
}

Token Tokenizer::getToken() {
	char c;
	if (file.eof()) {  // если файл изначально пустой, то бан
		std::cout << "Exhaused tokens" << std::endl;
	}
	c = getWithoutWhiteSpace();  // получаем токен

	Token token;
	if (c == '"') {  
		token.type = TOKEN::STRING;
		token.value = "";
		file.get(c);
		while (c != '"')
		{
			token.value += c;
			file.get(c);
		}
	}
	else if (c == '{') {
		token.type = TOKEN::CURLY_OPEN;
	}
	else if (c == '}') {
		token.type = TOKEN::CURLY_CLOSE;
	}
	else if (c == ':') {
		token.type = TOKEN::COLON;
	}
	else if (c == ',') {
		token.type = TOKEN::COMMA;
	}
	return token;
}

bool Tokenizer::hasMoreTokens(){
	return !file.eof();
}