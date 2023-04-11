#pragma once
#include <iostream>
#include <stack>
#include "Tokenizer.h"
#include "string"

namespace JsonLib {

    enum class ValueType { OBJECT, SRING }; // типы наших данных: или объект или строка

    class IValue {
    protected:
        std::string key;
    public:
        IValue(std::string _key) : key(_key) {}
        std::string getKey() { return key; }
        virtual ValueType getType() = 0;
        virtual bool is_null() = 0;
        virtual std::string toString() = 0;
    };

    struct Link {
        IValue* val;
        Link* next;
        Link(IValue* _val = nullptr, Link* _next = nullptr) : val(_val), next(_next) {}
        void setVal(IValue* _val) { val = _val; }
        std::string getVal() { return val->toString(); }
    };

    class strValue : public IValue {
        std::string val;
        Link* parent;
    public:
        strValue(
            std::string _key, 
            std::string _val,
            Link* _parent = nullptr) : IValue(_key) {  // parent - это родитель нашего поля. Это чтобы мы могли вернуться на уровень выше
            val = _val;
            parent = _parent;
        }
        ValueType getType() override { return ValueType::SRING; }
        std::string toString() override;  // Преобразование в красивую строку формата "<key>": "<value>",
        bool is_null() override;
    };

    class listValue : public IValue {
        Link* head;  // голова списка
        Link* last;  // последний элемеент списка
        listValue* parent;  // родитель список. Это нужно чтобы из любого поля мы смогли перескочить на уровень вышеa
    public:
        listValue(
            std::string _key = "",
            listValue* _parent = nullptr,
            Link * _head = new Link()) : IValue(_key) {  // по умолчанию в писке будет храниться пустой элемент
            head = _head;
            last = head;
            parent = _parent;
        }
        Link* get_head() { return head; }
        void add(Link* val);  // добавить новый эелемент в список
        ValueType getType() override { return ValueType::OBJECT; }
        listValue* getParent();
        std::string toString() override;  // Преобразование в красивую строку формата "<key>": { <value> }
        
        // ----------------------------------------------------------------------------------------------------------------

        bool is_null();

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
        listValue* root;  // изначально наш объект состоит из пустого списка. ВНИМАНИЕ! Этот указатель будет указывать не на "голову" списка всего Json, а на тот в котором мы сейчас находимся
        Tokenizer tokenizer;  // для распознавая объектов при чтении из файла. Подробнее в Tokenizer.h
        Link* current_el;  // текущий элемент на котором мы сейчас находимся 
        //std::stack<Link*> st;
    public:
        Json(std::string filename): tokenizer(filename){
            root = new listValue();
            current_el = nullptr;
        }
        std::string getString() {
            return root->toString();
        };
        void parse();  // парсинг из файла
        bool has_in();
        bool has_next();
        bool has_prev();

        void go_in();
        void go_out();
        void go_up();
        void go_down();

        //void load(std::string filename);
        //void save(std::string filename);
        //void add(std::string key, std::string value);  // добавить эелемент
        //void del();  // удалить элемент

        //void next(); // идём дальше
        //void down(); // идём в глубь
        //void up(); // идём наверх
    };
}


