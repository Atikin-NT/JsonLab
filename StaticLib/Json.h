#pragma once
#include <iostream>
#include "Tokenizer.h"
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
        //virtual std::string toString() = 0;
    };

    struct Link {
        IValue* val;
        Link* next;
        Link(IValue* _val = nullptr, Link* _next = nullptr) : val(_val), next(_next) {}
        void setVal(IValue* _val) {
            val = _val;
        }
        std::string getVal() {
            return val->getVal();
        }
    };

    class strValue : public IValue {
        std::string val;
        Link* parent;
    public:
        strValue(
            std::string _key, 
            std::string _val,
            Link* _parent = nullptr) : IValue(_key) {
            val = _val;
            parent = _parent;
        }
        ValueType getType() override {
            return ValueType::SRING;
        }
        std::string getVal() override {
            return val;
        }
    };

    class listValue : public IValue {
        Link* list;
        Link* last;
        listValue* parent;
    public:
        listValue(
            std::string _key = "",
            listValue* _parent = nullptr,
            Link * _list = new Link()) : IValue(_key) {
            list = _list;
            last = list;
            parent = _parent;
        }
        void add(Link* val);
        ValueType getType() override {
            return ValueType::OBJECT;
        }
        listValue* getParent() {
            if (parent == nullptr) {
                return this;
            }
            return parent;
        }
        std::string getVal() override {
            std::string val = "";
            Link* tmp = list->next;
            while (tmp != nullptr) {
                val += tmp->getVal();
                val += "   ";
                tmp = tmp->next;
            }
            
            return val;
        }

    };

    class Json {
        listValue* root;
        Tokenizer tokenizer;
        Link* current_el;
    public:
        Json(std::string filename): tokenizer(filename){
            root = new listValue();
            current_el = nullptr;
        }
        void parse();
        void load(std::string filename);
        //void save(std::string filename);
        void add(std::string key, Link* list);  // добавить эелемент
        //void add(std::string key, std::string value);  // добавить эелемент
        //void del();  // удалить элемент

        //void next(); // идём дальше
        //void down(); // идём в глубь
        //void up(); // идём наверх
    private:
        //void add_element();
    };
}


