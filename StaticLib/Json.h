#pragma once
#include <iostream>
#include <stack>
#include "Tokenizer.h"
#include "string"

namespace JsonLib {

    enum class ValueType { OBJECT, SRING }; // ���� ����� ������: ��� ������ ��� ������

    class IValue {
    protected:
        std::string key;
    public:
        IValue(std::string _key) : key(_key) {}
        std::string getKey() { return key; }
        virtual ValueType getType() = 0;
        virtual bool is_null() = 0;
        virtual std::string toString(std::string tab = "", IValue* currentKey = nullptr) = 0;
    };

    struct Link {
        IValue* val;
        ValueType type;
        Link* next;
        Link* prev;
        Link(Link* _prev, IValue* _val = nullptr, ValueType _type = ValueType::SRING, Link* _next = nullptr) : prev(_prev), val(_val), type(_type), next(_next) {}
        ~Link() {
            delete val;
        }
        void setVal(IValue* _val, ValueType _type = ValueType::SRING) {
            val = _val;
            type = _type;
        }
        std::string toString() { return val->toString(); }
    };

    class strValue : public IValue {
        std::string val;
        Link* parent;
    public:
        strValue(
            std::string _key, 
            std::string _val,
            Link* _parent = nullptr) : IValue(_key) {  // parent - ��� �������� ������ ����. ��� ����� �� ����� ��������� �� ������� ����
            val = _val;
            parent = _parent;
        }
        ~strValue() {}
        ValueType getType() override { return ValueType::SRING; }
        std::string getVal() { return val; }
        std::string toString(std::string tab = "", IValue* currentKey = nullptr) override;  // �������������� � �������� ������ ������� "<key>": "<value>",
        bool is_null() override;
    };

    class Iterator {
        Link *current;
        Link *head;
    public:
        Iterator(Link* _head);
        bool hasNext() { return current->next != nullptr; }
        void next();
        void back();

        IValue* getVal() { return current->val; }
        Link* getCurrent() { return current; }
        ValueType getType() { return current->type; }
    };

    class listValue : public IValue {
        Link* head;  // ������ ������
        Link* last;  // ��������� �������� ������
        listValue* parent;  // �������� ������. ��� ����� ����� �� ������ ���� �� ������ ����������� �� ������� ����a
    public:
        listValue(
            std::string _key = "",
            listValue* _parent = nullptr,
            Link * _head = new Link(nullptr)) : IValue(_key) {  // �� ��������� � ����� ����� ��������� ������ �������
            head = _head;
            last = head;
            parent = _parent;
        }
        ~listValue() {
            Link* tmp = head->next;
            while (tmp != last) {
                delete tmp->prev;
            }
            delete tmp;
        }
        Iterator getIter() { return Iterator(head); }
        Link* getHead() { return head; }
        Link* getFirst() { return head->next; }
        Link* getLast() { return last;  }
        void add(Link* val);  // �������� ����� �������� � ������
        ValueType getType() override { return ValueType::OBJECT; }
        listValue* getParent();
        std::string toString(std::string tab = "", IValue* currentKey = nullptr) override;  // �������������� � �������� ������ ������� "<key>": { <value> }
        bool is_null();
    };

    class Json {
        listValue* root;  // ���������� ��� ������ ������� �� ������� ������. ��������! ���� ��������� ����� ��������� �� �� "������" ������ ����� Json, � �� ��� � ������� �� ������ ���������
        Tokenizer tokenizer;  // ��� ����������� �������� ��� ������ �� �����. ��������� � Tokenizer.h
        Link* current_el;  // ������� ������� �� ������� �� ������ ��������� 
        std::stack<Iterator> iter_stack;
    public:
        Json(std::string filename) : tokenizer(filename) {
            root = new listValue();
            current_el = nullptr;
        }
        ~Json() {
            delete root;
        }
        std::string getString() {
            return root->toString("", iter_stack.top().getCurrent()->val);
        };
        void parse();  // ������� �� �����
        bool has_in();
        bool has_next();
        bool has_prev();

        void go_in();
        void go_out();
        void go_up();
        void go_down();

        void del();
        void setVal(std::string val);
        void addVal(std::string key, std::string val);

        void save_to_file(std::string filename);
    };
}


