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
        virtual std::string toString(std::string tab = "", IValue* currentKey = nullptr) = 0;
    };

    struct Link {
        IValue* val;
        ValueType type;
        Link* next;
        Link(IValue* _val = nullptr, ValueType _type = ValueType::SRING, Link* _next = nullptr) : val(_val), type(_type), next(_next) {}
        void setVal(IValue* _val, ValueType _type = ValueType::SRING) {
            val = _val;
            type = _type;
        }
        std::string toString() { return val->toString(); }
        //IValue* getVal() { return val; }
        //ValueType getType() { return type; }
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
        std::string toString(std::string tab = "", IValue* currentKey = nullptr) override;  // Преобразование в красивую строку формата "<key>": "<value>",
        bool is_null() override;
    };

    class Iterator {
        Link *current;
        Link *head;
        Link* prev;
    public:
        Iterator(Link* _head);
        bool hasNext() { return current->next != nullptr; }
        void next();

        IValue* getVal() { return current->val; }
        Link* getCurrent() { return current; }
        ValueType getType() { return current->type; }
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
        Iterator getIter() { return Iterator(head); }
        Link* getHead() { return head; }
        Link* getFirst() { return head->next; }
        void add(Link* val);  // добавить новый эелемент в список
        ValueType getType() override { return ValueType::OBJECT; }
        listValue* getParent();
        std::string toString(std::string tab = "", IValue* currentKey = nullptr) override;  // Преобразование в красивую строку формата "<key>": { <value> }
        bool is_null();
    };

    class Json {
        listValue* root;  // изначально наш объект состоит из пустого списка. ВНИМАНИЕ! Этот указатель будет указывать не на "голову" списка всего Json, а на тот в котором мы сейчас находимся
        Tokenizer tokenizer;  // для распознавая объектов при чтении из файла. Подробнее в Tokenizer.h
        Link* current_el;  // текущий элемент на котором мы сейчас находимся 
        std::stack<Iterator> iter_stack;
    public:
        Json(std::string filename): tokenizer(filename){
            root = new listValue();
            //current_el = nullptr;
        }
        std::string getString() {
            return root->toString("", iter_stack.top().getCurrent()->val);
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
        void save_to_file(std::string filename);
        //void add(std::string key, std::string value);  // добавить эелемент
        //void del();  // удалить элемент

        //void next(); // идём дальше
        //void down(); // идём в глубь
        //void up(); // идём наверх
    };
}


