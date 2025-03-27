#define CATCH_CONFIG_MAIN
#include "../catch2/catch.hpp"
#include "../LW2_5_ParseURL/ParseURL.h"

// Ожидаем успех команды
void ExpectCorrectURL(const std::string& url, Protocol expectedProtocol, const std::string& expectedHost, int expectedPort, const std::string& exepectedDocument)
{
	std::string host, document;
	Protocol protocol;
	int port;
	REQUIRE(ParseURL(url, protocol, port, host, document));
	CHECK(protocol == expectedProtocol);
	CHECK(port == expectedPort);
	CHECK(host == expectedHost);
	CHECK(document == exepectedDocument);
}

// Функция ParseURL извлекает протокол, хост, порт и документ из URL-а
TEST_CASE("Parse URL function extracts the protocol host port document from URL")
{
	ExpectCorrectURL("http://hostname:87/doc.txt", Protocol::HTTP, "hostname", 87, "doc.txt");
	ExpectCorrectURL("ftp://hostname:87/doc.txt", Protocol::FTP, "hostname", 87, "doc.txt");
	ExpectCorrectURL("https://hostname:87/doc.txt", Protocol::HTTPS, "hostname", 87, "doc.txt");
}

// Функция ParseURL если порт не указан, возвращает его в зависимости от протокола
TEST_CASE("Parse URL function determines port by protocol if the port is not specified")
{
	ExpectCorrectURL("http://www.mysite.com/doc.txt", Protocol::HTTP, "www.mysite.com", HTTP_PORT, "doc.txt");
	ExpectCorrectURL("ftp://www.mysite.com/doc.txt", Protocol::FTP, "www.mysite.com", FTP_PORT, "doc.txt");
	ExpectCorrectURL("https://www.mysite.com/doc.txt", Protocol::HTTPS, "www.mysite.com", HTTPS_PORT, "doc.txt");
}

// Функция ParseURL игнорирует регистр символа протокола
TEST_CASE("Parse URL function ignores the case of the protocol character")
{
	ExpectCorrectURL("HTTP://www.mysite.com/doc.txt", Protocol::HTTP, "www.mysite.com", HTTP_PORT, "doc.txt");
	ExpectCorrectURL("FTP://www.mysite.com/doc.txt", Protocol::FTP, "www.mysite.com", FTP_PORT, "doc.txt");
	ExpectCorrectURL("HTTPS://www.mysite.com/doc.txt", Protocol::HTTPS, "www.mysite.com", HTTPS_PORT, "doc.txt");
}

// Минимальный и максимальный допустимые порты корректны
TEST_CASE("The minimum and maximum allowed ports are correct")
{
	ExpectCorrectURL("http://www.mysite.com:1/doc.txt", Protocol::HTTP, "www.mysite.com", 1, "doc.txt");
	ExpectCorrectURL("http://www.mysite.com:65535/doc.txt", Protocol::HTTP, "www.mysite.com", 65535, "doc.txt");
}

// Функция ParseURL возвращает ошибку если номер порта вне диапазона 1-65535
TEST_CASE("Parse URL function returns an error if port number is out of range 1 65535")
{
	{
		Protocol protocol;
		int port;
		std::string host;
		std::string document;
		CHECK_FALSE(ParseURL("ftp://www.mysite.com:65536/doc.txt", protocol, port, host, document));
	}
	{
		Protocol protocol;
		int port;
		std::string host;
		std::string document;
		CHECK_FALSE(ParseURL("ftp://www.mysite.com:0/doc.txt", protocol, port, host, document));
	}
}

// Функция ParseURL возвращает true если документ пустой
TEST_CASE("Parse URL function returns an error if empty document")
{
	Protocol protocol;
	int port;
	std::string host;
	std::string document;
	CHECK(ParseURL("ftp://www.mysite.com", protocol, port, host, document));
}

// Функция ParseURL возвращает ошибку если порт не является числом
TEST_CASE("Parse URL function returns an error if port is not a number")
{
	Protocol protocol;
	int port;
	std::string host;
	std::string document;
	CHECK_FALSE(ParseURL("ftp://www.mysite.com:aa/doc.txt", protocol, port, host, document));
}

// Функция ParseURL возвращает ошибку если URL не содержит известных протоколов
TEST_CASE("Parse URL function returns an error if protocol is unknown")
{
	Protocol protocol;
	int port;
	std::string host;
	std::string document;
	CHECK_FALSE(ParseURL("ftps://www.mysite.com:56/doc.txt", protocol, port, host, document));
}

// Тесты для функции GetProtocol
TEST_CASE("GetProtocol function tests")
{
	SECTION("Valid protocols")
	{
		Protocol protocol;
		CHECK(GetProtocol("http", protocol));
		CHECK(protocol == Protocol::HTTP);

		CHECK(GetProtocol("HTTPS", protocol));
		CHECK(protocol == Protocol::HTTPS);

		CHECK(GetProtocol("Ftp", protocol));
		CHECK(protocol == Protocol::FTP);
	}

	SECTION("Invalid protocols")
	{
		Protocol protocol;
		CHECK_FALSE(GetProtocol("httpx", protocol));
		CHECK_FALSE(GetProtocol("", protocol));
		CHECK_FALSE(GetProtocol("http2", protocol));
		CHECK_FALSE(GetProtocol("ssh", protocol));
	}
}

// Тесты для функции GetPort
TEST_CASE("GetPort function tests")
{
	SECTION("Valid protocols")
	{
		CHECK(GetPort(Protocol::HTTP) == HTTP_PORT);
		CHECK(GetPort(Protocol::HTTPS) == HTTPS_PORT);
		CHECK(GetPort(Protocol::FTP) == FTP_PORT);
	}

	SECTION("Invalid protocol")
	{
		CHECK(GetPort(static_cast<Protocol>(-1)) == -1);
	}
}

// Некорректный формат URL
TEST_CASE("Invalid URL format")
{
	Protocol protocol;
	int port;
	std::string host;
	std::string document;
	CHECK_FALSE(ParseURL("http//www.mysite.com", protocol, port, host, document));
	CHECK_FALSE(ParseURL("http:/www.mysite.com", protocol, port, host, document));
	CHECK_FALSE(ParseURL("http:www.mysite.com", protocol, port, host, document));
	CHECK_FALSE(ParseURL("http://", protocol, port, host, document));
	CHECK_FALSE(ParseURL("http:///doc", protocol, port, host, document));
	CHECK_FALSE(ParseURL("http://:80/doc", protocol, port, host, document));
}

// Специальные символы в документе
TEST_CASE("Special characters in the document")
{
	ExpectCorrectURL("http://www.mysite.com/path%20with%20spaces", Protocol::HTTP, "www.mysite.com", HTTP_PORT, "path%20with%20spaces");
	ExpectCorrectURL("http://www.mysite.com/?query=param", Protocol::HTTP, "www.mysite.com", HTTP_PORT, "?query=param");
}

