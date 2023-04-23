#pragma once
#include <iostream>
#include "string"
#include "Json.h"


namespace MyDLL {
	
	public ref class Json {
		JsonLib::Json* json;
	public:
		Json() {
			json = nullptr;
		}
		Json(System::String^ addr) {
			std::string str = "";
			MarshalString(addr, str);
			json = new JsonLib::Json(str);
			json->parse();
		}
		void load(System::String^ addr) {
			delete json;
			std::string str = "";
			MarshalString(addr, str);
			json = new JsonLib::Json(str);
			json->parse();
		}
		System::String^ getString() {
			System::String^ str = gcnew System::String(json->getString().data());
			return str;
		}
		void MarshalString(System::String^ s, std::string& os) {
			using namespace System::Runtime::InteropServices;
			const char* chars = (const char*)(Marshal::StringToHGlobalAnsi(s)).ToPointer();
			os = chars;
			Marshal::FreeHGlobal(System::IntPtr((void*)chars));
		}
		void parse() { json->parse(); }

		void go_in() { json->go_in(); }
		void go_out() { json->go_out(); }
		void go_up() { json->go_up(); }
		void go_down() { json->go_down(); };

		void saveToFile(System::String^ filename) {
			std::string str = "";
			MarshalString(filename, str);
			json->save_to_file(str);
		}

		void del() { json->del(); }
		void setVal(System::String^ val) {
			std::string str = "";
			MarshalString(val, str);
			json->setVal(str);
		}
		void addVal(System::String^ key, System::String^ val) {

			std::string str1 = "";
			MarshalString(key, str1);

			std::string str2 = "";
			MarshalString(val, str2);

			json->addVal(str1, str2);
		}
	};

}
