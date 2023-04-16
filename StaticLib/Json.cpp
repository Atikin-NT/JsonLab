#include "Json.h"
#include "ValueTypes.h"
#include <fstream>
#include <stdexcept>
#include <iostream>


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
		//iter_stack.push(root->getIter());
		Link* current_el;

		while (tokenizer.hasMoreTokens()) { // пока есть токены, читаем файл
			Token token = tokenizer.getToken();
			//std::cout << "Type = " << token.getStringType() << " Value = " << token.value << std::endl;
			if (token.type == TOKEN::STRING) { // если токен строка (это будет ключ), то...
				key = token.value;
				current_el = new Link();

				token = tokenizer.getToken();
				if (token.type != TOKEN::COLON) { // если нет двоеточия, то кидаем ошибку
					throw std::logic_error("Read JSON error");
				}

				token = tokenizer.getToken();
				if (token.type == TOKEN::CURLY_OPEN) {  // если значенияе элемента новый объект, то ....
					listValue* newList = new listValue(key, root);
					current_el->setVal(newList, ValueType::OBJECT);
					root->add(current_el); // добаляем в наш список новый элемент
					root = newList;  // спускаемся на уровень ниже
				}
				else if (token.type == TOKEN::STRING) {  // если просто строка, то ....
					current_el->setVal(new strValue(key, token.value, current_el), ValueType::SRING);
					root->add(current_el);  // добаляем в наш список новый элемент
				}
			}
			else if (token.type == TOKEN::CURLY_CLOSE) { // если закрывающая скобка(конец объекта)
				root = root->getParent();  // переходим на уровень выше
			}
			// надо сделать обработчик запятой
		}
		//current_el = root->getFirst();
		//std::cout << getString() << std::endl;
		//listValue* tmp = (listValue*)current_el->val;
		iter_stack.push(root->getIter());
	}

	bool Json::has_in() {
		//Link* current_el = iter_stack.top().getCurrent();
		if (current_el->val->getType() == ValueType::OBJECT && !current_el->val->is_null())
			return true;
		return false;
	}

	bool Json::has_next() {
		//Link* current_el = iter_stack.top().getCurrent();
		if (current_el->next == nullptr)
			return false;
		return true;
	}

	bool Json::has_prev() {
		//Link* current_el = iter_stack.top().getCurrent();
		if (current_el->next == nullptr)
			return false;
		return true;
	}

	void Json::go_in() {
		Link* current_el = iter_stack.top().getCurrent();
		if (current_el->val->getType() == ValueType::OBJECT && !current_el->val->is_null()) {
			//Iterator new_iter((listValue*)current_el->val);
			//current_el = new_iter.getVal();
			iter_stack.push(((listValue*)current_el->val)->getIter());
			current_el = ((listValue*)current_el->val)->getFirst();
			//int tmp;
			//iter_stack.push(((listValue*)current_el->val)->getIter());
		}
	}

	void Json::go_out() {
		iter_stack.pop();
		Link* current_el = iter_stack.top().getCurrent();
		/*root = root->getParent();*/
	}

	void Json::go_down() {
		iter_stack.top().next();
	}

	void Json::go_up() {

	}


	void Json::save_to_file(std::string filename) {
		std::ofstream file;
		file.open(filename, std::ios::out);
		if (!file.good()) {
			throw std::logic_error("Open file for read");
		}

		file << root->toString();
	}
}