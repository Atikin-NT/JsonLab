#include "Json.h"
#include <fstream>


namespace JsonLib {
	void Json::load(std::string filename) {
		std::string getcontent;
		std::ifstream openfile;
		openfile.open(filename);
		if (openfile.is_open()) {
			while (!openfile.eof())
			{
				openfile >> getcontent;
				std::cout << getcontent << std::endl;
			}
		}
	}

	void Json::parse() {
		while (tokenizer.hasMoreTokens()) {
			tokenizer.getToken();
		}
	}
}