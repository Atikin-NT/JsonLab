#include "Json.h"
#include "ValueTypes.h"
#include <fstream>
#include <stdexcept>


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
			std::cout << "Type = " << token.getStringType() << " Value = " << token.value << std::endl;
			if (token.type == TOKEN::STRING) { // ���� ���� ������ (��� ����� ����), ��...
				key = token.value;
				current_el = new Link();

				token = tokenizer.getToken();
				if (token.type != TOKEN::COLON) { // ���� ��� ���������, �� ������ ������
					throw std::logic_error("Read JSON error");
				}

				token = tokenizer.getToken();
				if (token.type == TOKEN::CURLY_OPEN) {  // ���� ��������� �������� ����� ������, �� ....
					listValue* newList = new listValue(key, root);
					current_el->setVal(newList);
					root->add(current_el); // �������� � ��� ������ ����� �������
					root = newList;  // ���������� �� ������� ����
				}
				else if (token.type == TOKEN::STRING) {  // ���� ������ ������, �� ....
					current_el->setVal(new strValue(key, token.value, current_el));
					root->add(current_el);  // �������� � ��� ������ ����� �������
				}
			}
			else if (token.type == TOKEN::CURLY_CLOSE) { // ���� ����������� ������(����� �������)
				root = root->getParent();  // ��������� �� ������� ����
			}
			std::cout << root->toString() << std::endl;
			// ���� ������� ���������� �������
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