#pragma once
#include <iostream>
#include "string"
#include "Json.h"


namespace MyDLL {
	
	public ref class Json {
		JsonLib::Json* json;
	public:
		Json(System::String^ addr) {
			std::string str = "";
			MarshalString(addr, str);
			json = new JsonLib::Json(str);
			json->parse();
		}
		System::String^ getString() {
			System::String^ str = gcnew System::String(json->getString().data());
			return str;
		}
		System::String^ toString() {
			std::string val = "{\n";
			JsonLib::Link* linkVal = JsonLib::listValue::head->next;
			while (linkVal != nullptr) {
				if (linkVal->val->getType() == ValueType::OBJECT) {
					val += "\"" + linkVal->val->getKey() + "\":";
				}
				val += linkVal->getVal();
				linkVal = linkVal->next;
			}
			return val + "\n}\n";


			//System::String^ str = gcnew System::String((json->getString() + "\t" + "aaaa").data());
			//return str;
		}
		void MarshalString(System::String^ s, std::string& os) {
			using namespace System::Runtime::InteropServices;
			const char* chars = (const char*)(Marshal::StringToHGlobalAnsi(s)).ToPointer();
			os = chars;
			Marshal::FreeHGlobal(System::IntPtr((void*)chars));
		}
	};

}
