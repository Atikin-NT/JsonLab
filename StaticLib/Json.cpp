#include "Json.h"
#include <fstream>
#include <stdexcept>


namespace JsonLib {

	void listValue::add(Link* val) {
		last->next = val;
		last = last->next;
	}


	void Json::load(std::string filename) {
		std::string getcontent;
		std::ifstream openfile;
		openfile.open(filename);
		if (openfile.is_open()) {
			while (!openfile.eof())
			{
				openfile >> getcontent;
				std::cout << getcontent << std::endl;
			}
		}
	}

	void Json::add(std::string key, Link* list) {

	}

	void Json::parse() {
		Token token;
		if (tokenizer.hasMoreTokens()) {  // скипаем первую открывающуюся фигурную скобку в файле
			token = tokenizer.getToken();
			if (token.type != TOKEN::CURLY_OPEN) {
				throw std::logic_error("Read JSON error");
			}
		}
		std::string key;
		while (tokenizer.hasMoreTokens()) {
			Token token = tokenizer.getToken();
			std::cout << "Type = " << token.getStringType() << " Value = " << token.value << std::endl;
			if (token.type == TOKEN::STRING) {
				key = token.value;
				current_el = new Link();

				token = tokenizer.getToken();
				if (token.type != TOKEN::COLON) {
					throw std::logic_error("Read JSON error");
				}

				token = tokenizer.getToken();
				if (token.type == TOKEN::CURLY_OPEN) {
					listValue* newList = new listValue(key, root);
					current_el->setVal(newList);
					root->add(current_el);
					root = newList;
				}
				else if (token.type == TOKEN::STRING) {
					current_el->setVal(new strValue(key, token.value, current_el));
					root->add(current_el);
				}
			}
			else if (token.type == TOKEN::CURLY_CLOSE) {
				root = root->getParent();
			}
			std::cout << root->getVal() << std::endl;
			//else if (token.type)
		}
	}
}