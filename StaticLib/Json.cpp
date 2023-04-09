#include "Json.h"
#include <fstream>
#include <stdexcept>


namespace JsonLib {

	std::string strValue::toString() {
		return "\"" + key + "\":\"" + val + "\",\n";
	}

	std::string listValue::toString() {  // ��, ��� ������� � ����������
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
}