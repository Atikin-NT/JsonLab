#pragma once
#include <iostream>

//#ifdef MY_DLL
//#define MY_DLL_JSON __declspec(dllexport)
//#else
//#define MY_DLL_JSON __declspec(dllexport)
//#endif

//---------------------------
// Что это? 
namespace JsonLib {
	public ref class Json {
	public:
		Json() {
			printf("Hello");
		}
	};
}
//---------------------------


#include "string"

using namespace std;

class IterValue {};

class IValue {
public:
    virtual int getType() = 0;
    virtual IterValue* itr() = 0;
    virtual string getKey() = 0;
    virtual string getVal() = 0;
};

class strValue : public IValue {
    string key;
    string val;
public:

};

struct Link {
    Link* next;
    IValue* val;
};

class listValue : public IValue {
    Link* n;
    string key;
public:

};

class JSon {
    listValue* root;
public:
    void load(string filename) {};
    void save(string filename) {};

    void next(); // идём дальше
    void down(); // идём в глубь
    void beak(); // идём наверх
};


