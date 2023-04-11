#include "Json.h"
#include "ValueTypes.h"
#include <fstream>
#include <stdexcept>


namespace JsonLib {
	void Json::parse() {
		Token token;
		if (tokenizer.hasMoreTokens()) {  // скипаем первую открывающуюся фигурную скобку в файле
			token = tokenizer.getToken();
			if (token.type != TOKEN::CURLY_OPEN) { // если ее нет, то кидаем ошибку
				throw std::logic_error("Read JSON error");
			}
		}
		std::string key;
		while (tokenizer.hasMoreTokens()) { // пока есть токены, читаем файл
			Token token = tokenizer.getToken();
			std::cout << "Type = " << token.getStringType() << " Value = " << token.value << std::endl;
			if (token.type == TOKEN::STRING) { // если токе строка (это будет ключ), то...
				key = token.value;
				current_el = new Link();

				token = tokenizer.getToken();
				if (token.type != TOKEN::COLON) { // если нет двоеточия, то кидаем ошибку
					throw std::logic_error("Read JSON error");
				}

				token = tokenizer.getToken();
				if (token.type == TOKEN::CURLY_OPEN) {  // если значенияе элемента новый объект, то ....
					listValue* newList = new listValue(key, root);
					current_el->setVal(newList);
					root->add(current_el); // добаляем в наш список новый элемент
					root = newList;  // спускаемся на уровень ниже
				}
				else if (token.type == TOKEN::STRING) {  // если просто строка, то ....
					current_el->setVal(new strValue(key, token.value, current_el));
					root->add(current_el);  // добаляем в наш список новый элемент
				}
			}
			else if (token.type == TOKEN::CURLY_CLOSE) { // если закрывающая скобка(конец объекта)
				root = root->getParent();  // переходим на уровень выше
			}
			std::cout << root->toString() << std::endl;
			// надо сделать обработчик запятой
		}
	}

	bool Json::has_in() {
		if (current_el->val->getType() == ValueType::OBJECT && !current_el->val->is_null())
			return true;
		return false;
	}

	bool Json::has_next() {
		if (current_el->next == nullptr)
			return false;
		return true;
	}

	bool Json::has_prev() {
		if (current_el->next == nullptr)
			return false;
		return true;
	}

	void Json::go_in() {
		if (current_el->val->getType() == ValueType::OBJECT && !current_el->val->is_null())
			current_el = ((listValue*)current_el->val)->get_head();
	}

	void Json::go_out() {
		root = root->getParent();
	}

	void Json::go_down() {
		if (has_next())
			current_el = current_el->next;
	}
}