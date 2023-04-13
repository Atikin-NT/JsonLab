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
		void MarshalString(System::String^ s, std::string& os) {
			using namespace System::Runtime::InteropServices;
			const char* chars = (const char*)(Marshal::StringToHGlobalAnsi(s)).ToPointer();
			os = chars;
			Marshal::FreeHGlobal(System::IntPtr((void*)chars));
		}
		void parse() { json->parse(); }
	};

}
