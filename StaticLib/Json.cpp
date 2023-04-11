#include "Json.h"
#include <fstream>
#include <stdexcept>


namespace JsonLib {

	std::string strValue::toString() {
		return "\"" + key + "\":\"" + val + "\",\n";
	}

	std::string listValue::toString() {  // хз, как вывести с табул€цией
		std::string val = "{\n";
		Link* linkVal = head->next;
		while (linkVal != nullptr) {
			if (linkVal->val->getType() == ValueType::OBJECT) {
				val += "\"" + linkVal->val->getKey() + "\":";
			}
			val += linkVal->getVal();
			linkVal = linkVal->next;
		}
		return val + "\n}\n";
	}

	void listValue::add(Link* val) {
		last->next = val;
		last = last->next;
	}

	void Json::parse() {
		Token token;
		if (tokenizer.hasMoreTokens()) {  // скипаем первую открывающуюс€ фигурную скобку в файле
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
				if (token.type != TOKEN::COLON) { // если нет двоеточи€, то кидаем ошибку
					throw std::logic_error("Read JSON error");
				}

				token = tokenizer.getToken();
				if (token.type == TOKEN::CURLY_OPEN) {  // если значени€е элемента новый объект, то ....
					listValue* newList = new listValue(key, root);
					current_el->setVal(newList);
					root->add(current_el); // добал€ем в наш список новый элемент
					root = newList;  // спускаемс€ на уровень ниже
				}
				else if (token.type == TOKEN::STRING) {  // если просто строка, то ....
					current_el->setVal(new strValue(key, token.value, current_el));
					root->add(current_el);  // добал€ем в наш список новый элемент
				}
			}
			else if (token.type == TOKEN::CURLY_CLOSE) { // если закрывающа€ скобка(конец объекта)
				root = root->getParent();  // переходим на уровень выше
			}
			std::cout << root->toString() << std::endl;
			// надо сделать обработчик зап€той
		}
	}
}