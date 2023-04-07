#include "dll.h"
#include <iostream>
#include <string>
#include <iostream>

//void MarshalString(System::String^ s, std::string& os) {
//	using namespace System::Runtime::InteropServices;
//	const char* chars =
//		(const char*)(Marshal::StringToHGlobalAnsi(s)).ToPointer();
//	os = chars;
//	Marshal::FreeHGlobal(System::IntPtr((void*)chars));
//}
//
//namespace JsonLib {
//	void Json::load(System::String^ filename) {
//		std::string tmp = "123";
//		MarshalString(filename, tmp);
//		std::cout << tmp << std::endl;
//		tmp = "456";
//		std::cout << tmp << std::endl;
//	}
//}