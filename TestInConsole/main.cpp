#include "Json.h"

int main() {
	JsonLib::Json tmp("C:\\FucingTrash\\Programming\\Repozitories\\UNN-PROJ\\JsonLab\\data.json");
	//tmp.load("C:\\Users\\Atikin\\Desktop\\University\\основы программирования\\semestr 4\\JsonLab\\data.json");
	tmp.parse();
	return 0;
}