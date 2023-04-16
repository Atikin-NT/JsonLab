#include "Json.h"

int main() {
	JsonLib::Json tmp("C:\\Users\\Atikin\\Desktop\\University\\основы программирования\\semestr 4\\JsonLab\\data.json");
	//tmp.load("C:\\Users\\Atikin\\Desktop\\University\\основы программирования\\semestr 4\\JsonLab\\data.json");
	tmp.parse();

	std::cout << tmp.getString() << std::endl;


	tmp.go_in();
	std::cout << tmp.getString() << std::endl;

	tmp.go_down();


	std::cout << tmp.getString() << std::endl;
	
	
	//tmp.save_to_file("C:\\Users\\Atikin\\Desktop\\University\\основы программирования\\semestr 4\\JsonLab\\res.json");
	return 0;
}