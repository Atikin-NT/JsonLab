#include "Json.h"
#include "ValueTypes.h"
#include <fstream>
#include <stdexcept>
#include <iostream>


namespace JsonLib {

	void Json::parse() {
		Token token;
		if (tokenizer.hasMoreTokens()) {  // ������� ������ ������������� �������� ������ � �����
			token = tokenizer.getToken();
			if (token.type != TOKEN::CURLY_OPEN) { // ���� �� ���, �� ������ ������
				throw std::logic_error("Read JSON error");
			}
		}
		std::string key;

		while (tokenizer.hasMoreTokens()) { // ���� ���� ������, ������ ����
			Token token = tokenizer.getToken();
			if (token.type == TOKEN::STRING) { // ���� ����� ������ (��� ����� ����), ��...
				key = token.value;

				token = tokenizer.getToken();
				if (token.type != TOKEN::COLON) { // ���� ��� ���������, �� ������ ������
					throw std::logic_error("Read JSON error");
				}

				token = tokenizer.getToken();
				if (token.type == TOKEN::CURLY_OPEN) {  // ���� ��������� �������� ����� ������, �� ....
					current_el = new Link(root->getLast());
					listValue* newList = new listValue(key, root);
					current_el->setVal(newList, ValueType::OBJECT);
					root->add(current_el); // �������� � ��� ������ ����� �������
					root = newList;  // ���������� �� ������� ����
				}
				else if (token.type == TOKEN::STRING) {  // ���� ������ ������, �� ....
					current_el = new Link(root->getLast());
					current_el->setVal(new strValue(key, token.value, current_el), ValueType::SRING);
					root->add(current_el);  // �������� � ��� ������ ����� �������
				}
			}
			else if (token.type == TOKEN::CURLY_CLOSE) { // ���� ����������� ������(����� �������)
				root = root->getParent();  // ��������� �� ������� ����
			}
		}
		iter_stack.push(root->getIter());
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
		Link* current_el = iter_stack.top().getCurrent();
		if (current_el->val->getType() == ValueType::OBJECT && !current_el->val->is_null()) {
			iter_stack.push(((listValue*)current_el->val)->getIter());
			current_el = ((listValue*)current_el->val)->getFirst();
		}
	}

	void Json::go_out() {
		iter_stack.pop();
		Link* current_el = iter_stack.top().getCurrent();
	}

	void Json::go_down() {
		iter_stack.top().next();
	}

	void Json::go_up() {
		iter_stack.top().back();
	}

	void Json::del() {
		Link* current_el = iter_stack.top().getCurrent();
		current_el->prev->next = current_el->next;
		delete current_el;
		go_out();
	}

	void Json::setVal(std::string val) {
		Link* current_el = iter_stack.top().getCurrent();
		strValue* newVal = new strValue(current_el->val->getKey(), val);
		delete current_el->val;
		current_el->setVal(newVal);
	}

	void Json::addVal(std::string key, std::string val) {
		Link* current_el = iter_stack.top().getCurrent();
		if (current_el->type == ValueType::SRING) {
			std::string tmpKey = current_el->val->getKey();
			std::string tmpVal = ((strValue*)current_el->val)->getVal();
			delete current_el->val;
			current_el->setVal(new listValue(tmpKey));
			current_el->type = ValueType::OBJECT;
			((listValue*)current_el->val)->add(
				new Link(
					((listValue*)current_el->val)->getLast(),
					new strValue(key, val),
					ValueType::SRING
				)
			);
		}
		else if (current_el->type == ValueType::OBJECT) {
			((listValue*)current_el->val)->add(
				new Link(
					((listValue*)current_el->val)->getLast(),
					new strValue(key, val),
					ValueType::SRING
				)
			);
		}
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