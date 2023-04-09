#pragma once
#include <iostream>
#include "Tokenizer.h"
#include "string"

namespace JsonLib {

    enum class ValueType { OBJECT, SRING }; // ���� ����� ������: ��� ������ ��� ������

    class IValue {
    protected:
        std::string key;
    public:
        IValue(std::string _key) : key(_key) {}
        std::string getKey() {
            return key;
        }
        virtual ValueType getType() = 0;
        //virtual IterValue* itr() = 0;
        //virtual std::string getVal() = 0;
        virtual std::string toString() = 0;
    };

    struct Link {
        IValue* val;
        Link* next;
        Link(IValue* _val = nullptr, Link* _next = nullptr) : val(_val), next(_next) {}
        void setVal(IValue* _val) {
            val = _val;
        }
        std::string getVal() {
            return val->toString();
        }
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
        ValueType getType() override {
            return ValueType::SRING;
        }
        std::string toString() override;  // �������������� � �������� ������ ������� "<key>": "<value>",
    };

    class listValue : public IValue {
        Link* head;  // ������ ������
        Link* last;  // ��������� �������� ������
        listValue* parent;  // �������� ������. ��� ����� ����� �� ������ ���� �� ������ ����������� �� ������� ����a
    public:
        listValue(
            std::string _key = "",
            listValue* _parent = nullptr,
            Link * _head = new Link()) : IValue(_key) {  // �� ��������� � ����� ����� ��������� ������ �������
            head = _head;
            last = head;
            parent = _parent;
        }
        void add(Link* val);  // �������� ����� �������� � ������
        ValueType getType() override {
            return ValueType::OBJECT;
        }
        listValue* getParent() {
            if (parent == nullptr) { // ��� �������� �����, �� ����� ������ ������ �� ������ Json �� ����� �������z
                return this;  //  � ����� �� ���� �����, ��������� ��� �������
            }
            return parent;
        }
        std::string toString() override;  // �������������� � �������� ������ ������� "<key>": { <value> }
        
        // ----------------------------------------------------------------------------------------------------------------

        Link* getHead() {
            return head;
        }

    };

    //class Iterator {
    //    Link* root;
    //public:
    //    Iterator(Link* head) : root(head) {};
    //    bool hasNext() {
    //        if (root->next != nullptr) return true;
    //        else return false;
    //    }

    //    IValue* next() {
    //        IValue* val;
    //        if (!hasNext()) throw - 1;
    //        Link* l = root.




    //    }
    //};

    class Json {
        listValue* root;  // ���������� ��� ������ ������� �� ������� ������. ��������! ���� ��������� ����� ��������� �� �� "������" ������ ����� Json, � �� ��� � ������� �� ������ ���������
        Tokenizer tokenizer;  // ��� ����������� �������� ��� ������ �� �����. ��������� � Tokenizer.h
        Link* current_el;  // ������� ������� �� ������� �� ������ ��������� 
    public:
        Json(std::string filename): tokenizer(filename){
            root = new listValue();
            current_el = nullptr;
        }
        std::string getString();
        void parse();  // ������� �� �����
        //void load(std::string filename);
        //void save(std::string filename);
        //void add(std::string key, std::string value);  // �������� ��������
        //void del();  // ������� �������

        //void next(); // ��� ������
        //void down(); // ��� � �����
        //void up(); // ��� ������
    };
}


