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
	CHECK(tie(protocol, port, host, document) == tie(expectedProtocol, expectedPort, expectedHost, exepectedDocument));
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

// Функция ParseURL возвращает ошибку если номер порта вне диапазона 1-65535
TEST_CASE("Parse URL function returns an error if port number is out of range 1 65535")
{
	{
		Protocol protocol;
		int port;
		std::string host;
		std::string document;
		CHECK(!ParseURL("ftp://www.mysite.com:65536/doc.html", protocol, port, host, document));
	}
	{
		Protocol protocol;
		int port;
		std::string host;
		std::string document;
		CHECK(!ParseURL("ftp://www.mysite.com:0/doc.html", protocol, port, host, document));
	}
}

// Функция ParseURL возвращает ошибку если документ пустой
TEST_CASE("Parse URL function returns an error if empty document")
{
	Protocol protocol;
	int port;
	std::string host;
	std::string document;
	CHECK(!ParseURL("ftp://www.mysite.com", protocol, port, host, document));
}

// Функция ParseURL возвращает ошибку если порт не является числом
TEST_CASE("Parse URL function returns an error if port is not a number")
{
	Protocol protocol;
	int port;
	std::string host;
	std::string document;
	CHECK(!ParseURL("ftp://www.mysite.com:aa/doc.txt", protocol, port, host, document));
}

// Функция ParseURL возвращает ошибку если URL не содержит известных протоколов
TEST_CASE("Parse URL function returns an error if protocol is unknown")
{
	Protocol protocol;
	int port;
	std::string host;
	std::string document;
	CHECK(!ParseURL("ftps://www.mysite.com:56/doc.txt", protocol, port, host, document));
}
