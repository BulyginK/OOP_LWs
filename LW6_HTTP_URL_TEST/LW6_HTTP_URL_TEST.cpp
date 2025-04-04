// HTTP_URL_test.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#define CATCH_CONFIG_MAIN
#include <iostream>
#include "../LW6_HTTP_URL/CHttpUrl.h"
#include "../LW6_HTTP_URL/CUrlParsingError.h"
#include "../catch2/catch.hpp"

// Конструктор с 1 параметром (url)
TEST_CASE("url constructor with 1 parameter")
{
	// URL в нижнем регистре
	SECTION("url in low letters")
	{
		CHttpUrl url("http://testurl.ru:8025/image.png/");
		CHECK(url.GetURL() == "http://testurl.ru:8025/image.png/");
		CHECK(url.GetProtocol() == Protocol::HTTP);
		CHECK(url.GetPort() == 8025);
		CHECK(url.GetDomain() == "testurl.ru");
		CHECK(url.GetDocument() == "/image.png/");
	}
	// URL в верхнем регистре
 	SECTION("full url in capital letters")
	{
		CHttpUrl url("https://TESTURL.RU:8025/image.png/");
		CHECK(url.GetURL() == "https://testurl.ru:8025/image.png/");
		CHECK(url.GetProtocol() == Protocol::HTTPS);
		CHECK(url.GetPort() == 8025);
		CHECK(url.GetDomain() == "testurl.ru");
		CHECK(url.GetDocument() == "/image.png/");
	}
	// HTTP без порта
	SECTION("url without port - http")
	{
		CHttpUrl url("http://testurl.ru/image.png/");
		CHECK(url.GetURL() == "http://testurl.ru/image.png/");
		CHECK(url.GetProtocol() == Protocol::HTTP);
		CHECK(url.GetPort() == 80);
		CHECK(url.GetDomain() == "testurl.ru");
		CHECK(url.GetDocument() == "/image.png/");
	}
	// HTTPS без порта
	SECTION("url without port - https")
	{
		CHttpUrl url("https://testurl.ru/image.png/");
		CHECK(url.GetURL() == "https://testurl.ru/image.png/");
		CHECK(url.GetProtocol() == Protocol::HTTPS);
		CHECK(url.GetPort() == 443);
		CHECK(url.GetDomain() == "testurl.ru");
		CHECK(url.GetDocument() == "/image.png/");
	}
	// Некорректный порт 0
	SECTION("url with 0 port")
	{
		REQUIRE_THROWS_WITH(CHttpUrl("https://testurl.ru:0/image.png/"), "Port value 0 is out of range [1-65535]");
	}
	// Некорректный порт 65536
	SECTION("url with 65536 port")
	{
		REQUIRE_THROWS_WITH(CHttpUrl("https://testurl.com:65536/image.png/"), "Port value 65536 is out of range [1-65535]");
	}
	// Минимальный допустимый порт (1)
	SECTION("url with port 1")
	{
		CHttpUrl url("https://testurl.ru:1/image.png/");
		CHECK(url.GetURL() == "https://testurl.ru:1/image.png/");
		CHECK(url.GetProtocol() == Protocol::HTTPS);
		CHECK(url.GetPort() == 1);
		CHECK(url.GetDomain() == "testurl.ru");
		CHECK(url.GetDocument() == "/image.png/");
	}
	// Максимально допустимый порт (65535)
	SECTION("url with port 65535")
	{
		CHttpUrl url("https://testurl.ru:65535/image.png/");
		CHECK(url.GetURL() == "https://testurl.ru:65535/image.png/");
		CHECK(url.GetProtocol() == Protocol::HTTPS);
		CHECK(url.GetPort() == 65535);
		CHECK(url.GetDomain() == "testurl.ru");
		CHECK(url.GetDocument() == "/image.png/");
	}
	// IP-адрес вместо домена
	SECTION("ip address")
	{
		CHttpUrl url("https://127.0.0.1:65535/image.png/");
		CHECK(url.GetURL() == "https://127.0.0.1:65535/image.png/");
		CHECK(url.GetProtocol() == Protocol::HTTPS);
		CHECK(url.GetPort() == 65535);
		CHECK(url.GetDomain() == "127.0.0.1");
		CHECK(url.GetDocument() == "/image.png/");
	}
	// Пустой документ
	SECTION("Empty document") {
		CHttpUrl url("http://example.com");
		CHECK(url.GetDocument() == "/");
		CHECK(url.GetURL() == "http://example.com");
	}
	// Только слеш
	SECTION("Single slash document") {
		CHttpUrl url("http://example.com/");
		CHECK(url.GetDocument() == "/");
		CHECK(url.GetURL() == "http://example.com");
	}
	// Только порт и слеш
	SECTION("Port with single slash document")
	{
		CHttpUrl url("https://test.com:8025/");
		CHECK(url.GetURL() == "https://test.com:8025");
		CHECK(url.GetPort() == 8025);
		CHECK(url.GetDocument() == "/");
	}
	// Множественные слеши
	SECTION("Multiple slashes") {
		CHttpUrl url("http://example.com///path//");
		CHECK(url.GetDocument() == "///path//");
	}
	// Некорректные домены
	SECTION("Invalid domains") {
		REQUIRE_THROWS_WITH(CHttpUrl("http://-test.com"), "Invalid URL");
		REQUIRE_THROWS_WITH(CHttpUrl("http://test-.com"), "Invalid URL");
		REQUIRE_THROWS_WITH(CHttpUrl("http://test..com"), "Invalid URL");
		REQUIRE_THROWS_WITH(CHttpUrl("http://test--com"), "Invalid URL");
	}
	// Некорректные URL
	SECTION("invalid url in capital letters")
	{
		REQUIRE_THROWS_WITH(CHttpUrl("htt://invalidurl:8025/testdocument/"), "Invalid URL");	// Неверный протокол (htt://)
		REQUIRE_THROWS_WITH(CHttpUrl("https:/invalidurl:8025/testdocument/"), "Invalid URL");	// Пропущен слэш (https:/)
		REQUIRE_THROWS_WITH(CHttpUrl("https:invalidurl:8025/testdocument/"), "Invalid URL");	// Неверный формат (https:)
		REQUIRE_THROWS_WITH(CHttpUrl("htt://invalid url"), "Invalid URL");						// Пробел в домене
		REQUIRE_THROWS_WITH(CHttpUrl("htt://invalidurl:8025/test document/"), "Invalid URL");	// Пробел в докуменете
	}
}
// Конструктор с 3 параметрами (домен, документ, протокол)
TEST_CASE("url constructor with 3 parameters")
{
	// Только домен и документ (протокол по умолчанию — HTTP)
	SECTION("url with domain and document, without Protocol")
	{
		CHttpUrl url("test.com", "image");
		CHECK(url.GetURL() == "http://test.com/image");
		CHECK(url.GetProtocol() == Protocol::HTTP);
		CHECK(url.GetPort() == 80);
		CHECK(url.GetDomain() == "test.com");
		CHECK(url.GetDocument() == "/image");
	}
	// Явное указание протокола HTTP
	SECTION("url with domain, document and protocol")
	{
		CHttpUrl url("test.com", "/image.png", Protocol::HTTP);
		CHECK(url.GetURL() == "http://test.com/image.png");
		CHECK(url.GetProtocol() == Protocol::HTTP);
		CHECK(url.GetPort() == 80);
		CHECK(url.GetDomain() == "test.com");
		CHECK(url.GetDocument() == "/image.png");
	}
	// Длинный путь документа
	SECTION("url with domain, document (long) and protocol")
	{
		CHttpUrl url("test.ru", "/path/to/document/", Protocol::HTTP);
		CHECK(url.GetURL() == "http://test.ru/path/to/document/");
		CHECK(url.GetProtocol() == Protocol::HTTP);
		CHECK(url.GetPort() == 80);
		CHECK(url.GetDomain() == "test.ru");
		CHECK(url.GetDocument() == "/path/to/document/");
	}
	// Некорректные параметры (пустые строки)
	SECTION("invalid parameters")
	{
		REQUIRE_THROWS_AS(CHttpUrl("test.ru", "", Protocol::HTTP), std::invalid_argument);
		REQUIRE_THROWS_AS(CHttpUrl("", "path", Protocol::HTTP), std::invalid_argument);
		REQUIRE_THROWS_AS(CHttpUrl("", "path"), std::invalid_argument);
	}
}
// Конструктор с 4 параметрами (домен, документ, протокол, порт)
TEST_CASE("url constructor with 4 parameters")
{
	// Все параметры (HTTP, порт 8080)
	SECTION("url with domain, document, protocol, port")
	{
		CHttpUrl url("test.com", "path/to/image.png", Protocol::HTTP, 8080);
		CHECK(url.GetURL() == "http://test.com:8080/path/to/image.png");
		CHECK(url.GetProtocol() == Protocol::HTTP);
		CHECK(url.GetPort() == 8080);
		CHECK(url.GetDomain() == "test.com");
		CHECK(url.GetDocument() == "/path/to/image.png");
	}
	// HTTPS с портом 80 (нестандартный порт для HTTPS)
	SECTION("url with domain, document, protocol, port (non-standard HTTPS - 80)")
	{
		CHttpUrl url("test.com", "/image.png", Protocol::HTTPS, 80);
		CHECK(url.GetURL() == "https://test.com:80/image.png");
		CHECK(url.GetProtocol() == Protocol::HTTPS);
		CHECK(url.GetPort() == 80);
		CHECK(url.GetDomain() == "test.com");
		CHECK(url.GetDocument() == "/image.png");
	}
	// HTTP с портом 443 (нестандартный порт для HTTP)
	SECTION("url with domain, document, protocol, port (non-standard HTTP - 443)")
	{
		CHttpUrl url("test.com", "/image.png", Protocol::HTTP, 443);
		CHECK(url.GetURL() == "http://test.com:443/image.png");
		CHECK(url.GetProtocol() == Protocol::HTTP);
		CHECK(url.GetPort() == 443);
		CHECK(url.GetDomain() == "test.com");
		CHECK(url.GetDocument() == "/image.png");
	}
	// Некорректный порт 0
	SECTION("url with domain, document, protocol, port 0")
	{
		REQUIRE_THROWS_WITH(CHttpUrl("test.ru", "/path/to/document/", Protocol::HTTP, 0), "Port value 0 is out of range [1-65535]");
	}
	// Пустые параметры
	SECTION("invalid parameters")
	{
		REQUIRE_THROWS_AS(CHttpUrl("test.ru", "", Protocol::HTTP, 8080), std::invalid_argument);
		REQUIRE_THROWS_AS(CHttpUrl("", "path", Protocol::HTTP, 200), std::invalid_argument);
		REQUIRE_THROWS_AS(CHttpUrl("", "", Protocol::HTTP, 200), std::invalid_argument);
	}
}