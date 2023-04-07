#pragma once
#include <iostream>
#include "string"
#include "Json.h"


namespace MyDLL {
	
	public ref class Json {
		JsonLib::Json* json;
	public:
		Json() {
			json = new JsonLib::Json();
		}
	};

}
