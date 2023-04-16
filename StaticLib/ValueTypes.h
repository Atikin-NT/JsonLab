#pragma once


namespace JsonLib {
	bool strValue::is_null() {
		if (val == "")
			return true;
		return false;
	}

	std::string strValue::toString(std::string tab, IValue* currentKey) {
		return "\"" + key + "\": \"" + val + "\"";
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

	std::string listValue::toString(std::string tab, IValue* currentKey) {

		std::string str = "{\n";
		Iterator i(head);
		while (true) {
			IValue* el = i.getVal();
			str += tab + "    ";
			if (el == currentKey) str += "$*$";

			if (el->getType() == ValueType::SRING) {
				strValue* s = static_cast<strValue*>(el);
				str += s->toString();
			}
			else if (el->getType() == ValueType::OBJECT) {
				listValue* l = static_cast<listValue*>(el);
				str += "\"" + l->getKey() + "\": ";
				str += l->toString(tab + "    ", currentKey);
			}
			//std::cout << i.hasNext() << std::endl;
			if (i.hasNext()) str += ",";
			str += "\n";

			if (i.hasNext()) i.next();
			else break;
		}
		return str + tab + "}";
	}

	void listValue::add(Link* val) {
		last->next = val;
		last = last->next;
	}

	// Iterator ---------------------------

	Iterator::Iterator(Link* _head) : head(_head) {
		if (head->next != nullptr) {
			current = head->next;
		}
		else throw - 1;
	}
	void Iterator::next() {
		if (hasNext()) {
			current = current->next;
		}
	}

	void Iterator::back() {
		if (getCurrent()->prev != nullptr) {
			current = getCurrent()->prev;
		}
	}

}