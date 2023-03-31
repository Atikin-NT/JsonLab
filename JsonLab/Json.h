#pragma once
#include <iostream>

//#ifdef MY_DLL
//#define MY_DLL_JSON __declspec(dllexport)
//#else
//#define MY_DLL_JSON __declspec(dllexport)
//#endif

namespace JsonLib {
	public ref class Json {
	public:
		Json() {
			printf("Hello");
		}
	};
}