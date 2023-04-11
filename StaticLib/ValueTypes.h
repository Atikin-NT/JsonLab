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
		if (parent == nullptr) // эта проверка нужна, тк самый первый список из класса Json не имеет родителz
			return this;  //  и чтобы не было ошики, возращаем его самомго
		return parent;
	}

	bool listValue::is_null() {
		if (head == last)
			return true;
		return false;
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
}