#include "pch.h"
#include "Json.h"

TEST(TestCaseName, TestName) {
	JsonLib::Json tmp;
	tmp.load("C:\\Users\\Atikin\\Desktop\\University\\������ ����������������\\semestr 4\\JsonLab\\data.json");
	EXPECT_EQ(1, 1);
	EXPECT_TRUE(true);
}