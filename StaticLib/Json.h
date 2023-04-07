#pragma once
#include <iostream>
#include "JsonParser.h"
#include "string"

namespace JsonLib {

    enum class ValueType { OBJECT, SRING };

    class IValue {
        std::string key;
    public:
        IValue(std::string _key) : key(_key) {}
        std::string getKey() {
            return key;
        }
        virtual ValueType getType() = 0;
        //virtual IterValue* itr() = 0;
        virtual std::string getVal() = 0;
        virtual std::string toString() = 0;
    };

    struct Link {
        IValue* val;
        Link* next;
        Link(IValue* _val = nullptr, Link* _next = nullptr) : val(_val), next(_next) {}
    };

    class strValue : public IValue {
        std::string val;
    public:
        strValue(std::string _key, std::string _val) : IValue(_key) {
            val = _val;
        }
        ValueType getType() override {
            return ValueType::SRING;
        }
    };

    class listValue : public IValue {
        Link* list;
        std::string key;
    public:
        listValue(Link* _list, std::string _key) : IValue(_key) {
            list = _list;
        }
        ValueType getType() override {
            return ValueType::OBJECT;
        }
    };

    class Json {
        listValue* root;
        Tokenizer tokenizer;
    public:
        Json(std::string filename): tokenizer(filename){
            root = nullptr;
        }
        void parse();
        void load(std::string filename);
        //void save(std::string filename);
        //void add();  // �������� ��������
        //void del();  // ������� �������

        //void next(); // ��� ������
        //void down(); // ��� � �����
        //void up(); // ��� ������
    private:
        //void add_element();
    };
}


