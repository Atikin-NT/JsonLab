#pragma once


namespace JsonLib {
	bool strValue::is_null() {
		if (val == "")
			return true;
		return false;
	}

	std::string strValue::toString() {
		return "\"" + key + "\":\"" + val + "\",\n";
	}

	listValue* listValue::getParent() {
		if (parent == nullptr) // ��� �������� �����, �� ����� ������ ������ �� ������ Json �� ����� �������z
			return this;  //  � ����� �� ���� �����, ��������� ��� �������
		return parent;
	}

	bool listValue::is_null() {
		if (head == last)
			return true;
		return false;
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
}