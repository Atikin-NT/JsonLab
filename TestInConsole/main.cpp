#include "Json.h"

int main() {
	JsonLib::Json tmp("C:\\Users\\Atikin\\Desktop\\University\\������ ����������������\\semestr 4\\JsonLab\\data.json");
	//tmp.load("C:\\Users\\Atikin\\Desktop\\University\\������ ����������������\\semestr 4\\JsonLab\\data.json");
	tmp.parse();
	return 0;
}