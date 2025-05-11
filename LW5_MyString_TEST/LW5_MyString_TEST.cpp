#define CATCH_CONFIG_MAIN
#include "../catch2/catch.hpp"
#include "../LW5_MyString/CMyString.h"

TEST_CASE("default constructor")
{
	CMyString myStr;
	CHECK(myStr.GetLength() == 0);
	CHECK(myStr.GetStringData()[0] == '\0');
	CHECK(myStr.GetStringData() == CMyString().GetStringData());
}

TEST_CASE("constructor: MyString(const char * pString)")
{
	char testStr[] = "Hello, World!";
	// конструктор инициаизирован с начала строки
	SECTION("construction string the same as original")
	{
		CMyString myStr(testStr);
		CHECK(myStr.GetLength() == 13);
		CHECK(myStr.GetStringData()[13] == '\0');
		CHECK(strcmp(testStr, myStr.GetStringData()) == 0);
		CHECK(myStr.GetStringData() != CMyString().GetStringData());
		// strcmp - сравнивает две строки лексикографически (по алфавиту)
		// str1, str2 — указатели на сравниваемые C-строки (должны заканчиваться нуль-терминатором \-0).
		// 0, если строки идентичны.
		// Отрицательное число, если str1 < str2 (по алфавиту).
		// Положительное число, если str1 > str2 (по алфавиту).
	}
	// конструктор инициаизирован НЕ с начала строки
	SECTION("construction string not from begin of original string")
	{
		CMyString myStr(&testStr[3]);
		CHECK(myStr.GetLength() == 10);
		CHECK(myStr.GetStringData()[10] == '\0');
		char expectedStr[] = "lo, World!";
		CHECK(strcmp(expectedStr, myStr.GetStringData()) == 0);
	}
	
	char testStr2[] = "Hel\0lo, World!";
	// конструктор инициаизирован строкой с \0
	SECTION("construction string with 0")
	{
		CMyString myStr(testStr2);
		CHECK(myStr.GetLength() == 3);
		CHECK(myStr.GetStringData()[3] == '\0');
		char expectedStr[] = "Hel";
		CHECK(strcmp(expectedStr, myStr.GetStringData()) == 0);
	}
}

TEST_CASE("constructor: MyString(const char * pString, size_t length)")
{
	SECTION("constructing string-1")
	{
		char testStr[] = "Calculator";
		CMyString myStr(testStr, 4);
		CHECK(myStr.GetLength() == 4);
		CHECK(myStr.GetStringData()[4] == '\0');
		char expectedStr[] = "Calc";
		CHECK(strcmp(expectedStr, myStr.GetStringData()) == 0);
	}
	SECTION("constructing string-2")
	{
		char testStr[] = "Calcul\0ator";
		CMyString myStr(&testStr[2], 7);
		CHECK(myStr.GetLength() == 7);
		CHECK(myStr.GetStringData()[7] == '\0');
		CHECK(CMyString("lcul\0at", 7) == myStr);
	}
	SECTION("constructing string with length 0")
	{
		char testStr[] = "Calculator";
		CMyString myStr(testStr, 0);
		CHECK(myStr.GetLength() == 0);
		CHECK(myStr.GetStringData()[0] == '\0');
		CHECK(myStr.GetStringData() == CMyString().GetStringData());
	}
	SECTION("constructing string that contains null code in the middle")
	{
		char testStr[] = "Calcul\0ator";
		CMyString myStr(testStr, 9);
		CHECK(myStr.GetLength() == 9);
		CHECK(myStr.GetStringData()[9] == '\0');
		CHECK(CMyString("Calcul\0at", 9) == myStr);
	}
}

TEST_CASE("copy constructor")
{
	SECTION("copying not empty string")
	{
		CMyString originalStr("Hello\0World!", 12);
		CMyString copiedStr(originalStr);
		CHECK(copiedStr.GetLength() == 12);
		CHECK(copiedStr.GetStringData()[12] == '\0');
		CHECK(CMyString("Hello\0World!", 12) == copiedStr);
		CHECK(copiedStr.GetStringData() != CMyString().GetStringData());
	}
	SECTION("copying empty string")
	{
		CMyString originalStr;
		CMyString copiedStr(originalStr);
		CHECK(copiedStr.GetLength() == 0);
		CHECK(copiedStr.GetStringData()[0] == '\0');
		CHECK(copiedStr.GetStringData() == CMyString().GetStringData());
	}
}

TEST_CASE("move constructor")
{
	SECTION("moving not empty string")
	{
		CMyString originalStr("Hello\0World!", 12);
		const char* originalData = originalStr.GetStringData();
		CMyString movedStr(std::move(originalStr));

		CHECK(movedStr.GetLength() == 12);
		CHECK(movedStr.GetStringData() == originalData);

		// Проверяем состояние originalStr после перемещения
		CHECK(originalStr.GetLength() == 0);
		CHECK(originalStr.GetStringData()[0] == '\0');
		// Проверяем, что используется статическая пустая строка
		CHECK(originalStr.GetStringData() == CMyString().GetStringData());
	}


	SECTION("moving empty string")
	{
		// Вызывается конструктор по умолчанию, 
		// который инициализирует originalStr как пустую строку (указатель m_pString указывает на статический s_emptyString).
		CMyString originalStr;
		// Запоминаем адрес данных исходной строки (это будет указатель на статический s_emptyString)
		const char* originalData = originalStr.GetStringData();
		CMyString movedStr(std::move(originalStr));

		CHECK(movedStr.GetLength() == 0);
		CHECK(movedStr.GetStringData() == originalData);

		// Проверяем состояние originalStr после перемещения
		CHECK(originalStr.GetLength() == 0);
		CHECK(originalStr.GetStringData()[0] == '\0');
		// Проверяем, что используется статическая пустая строка
		CHECK(originalStr.GetStringData() == CMyString().GetStringData());
	}
}

TEST_CASE("constructor: MyString(std::string const& stlString)")
{
	SECTION("construction not empty string")
	{
		std::string testStr = "Hello World!";
		CMyString myStr(testStr);
		CHECK(myStr.GetLength() == 12);
		CHECK(myStr.GetStringData()[12] == '\0');
		CHECK(strcmp(testStr.c_str(), myStr.GetStringData()) == 0);
	}
	SECTION("construction empty string")
	{
		std::string testStr;
		CMyString myStr(testStr);
		CHECK(myStr.GetLength() == 0);
		CHECK(myStr.GetStringData()[0] == '\0');
		CHECK(strcmp(testStr.c_str(), myStr.GetStringData()) == 0);
	}

	SECTION("verify deep copy independence")
	{
		std::string testStr = "Test";
		CMyString myStr(testStr);
		testStr[0] = 'B';
		CHECK(strcmp(myStr.GetStringData(), "Test") == 0);
	}

	{
		CMyString myStr(std::string("Temporary"));
		CHECK(myStr.GetLength() == 9);
		CHECK(strcmp(myStr.GetStringData(), "Temporary") == 0);
	}
}

TEST_CASE("СMyString::SubString")
{
	CMyString myStr("Computer");
	SECTION("creating substring-1")
	{
		CMyString subStr = myStr.SubString(0, 5);
		CHECK(subStr.GetLength() == 5);
		CHECK(subStr.GetStringData()[5] == '\0');
		CHECK(CMyString("Compu") == subStr);
	}
	SECTION("creating substring-2")
	{
		CMyString subStr = myStr.SubString(7, 1);
		CHECK(subStr.GetLength() == 1);
		CHECK(subStr.GetStringData()[1] == '\0');
		CHECK(CMyString("r") == subStr);
	}
	SECTION("creating empty substring")
	{
		CMyString subStr = myStr.SubString(3, 0);
		CHECK(subStr.GetLength() == 0);
		CHECK(subStr.GetStringData()[0] == '\0');
		CHECK(CMyString("") == subStr);
	}
}

TEST_CASE("Clear method tests")
{
	SECTION("Clear non-empty string")
	{
		CMyString str("Hello");
		str.Clear();
		CHECK(str.GetLength() == 0);
		CHECK(strcmp(str.GetStringData(), "") == 0);
		CHECK(str.GetStringData() == CMyString().GetStringData());
	}

	SECTION("Clear empty string")
	{
		CMyString str;
		str.Clear();
		CHECK(str.GetLength() == 0);
		CHECK(strcmp(str.GetStringData(), "") == 0);
	}

	SECTION("Double clear")
	{
		CMyString str("Test");
		str.Clear();
		str.Clear();
		CHECK(str.GetLength() == 0);
	}
}