// HTTP_URL_test.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#define CATCH_CONFIG_MAIN
#include <iostream>
#include "../LW6_HTTP_URL/CHttpUrl.h"
#include "../LW6_HTTP_URL/CUrlParsingError.h"
#include "../catch2/catch.hpp"

void CheckUrlProperties(
	const CHttpUrl& url,                     
	const std::string& expectedUrl,         
	Protocol expectedProtocol,             
	unsigned short expectedPort,            
	const std::string& expectedDomain,      
	const std::string& expectedDocument     
) {
	CHECK(url.GetURL() == expectedUrl);
	CHECK(url.GetProtocol() == expectedProtocol);
	CHECK(url.GetPort() == expectedPort);
	CHECK(url.GetDomain() == expectedDomain);
	CHECK(url.GetDocument() == expectedDocument);
}

TEST_CASE("url constructor with 1 parameter")
{
	SECTION("url in low letters")
	{
		CHttpUrl url("http://testurl.ru:8025/image.png/");
		CheckUrlProperties(url,
			"http://testurl.ru:8025/image.png/",
			Protocol::HTTP,
			8025,
			"testurl.ru",
			"/image.png/");
	}

	SECTION("full url in capital letters")
	{
		CHttpUrl url("https://TESTURL.RU:8025/image.png/");
		CheckUrlProperties(url,
			"https://testurl.ru:8025/image.png/",
			Protocol::HTTPS,
			8025,
			"testurl.ru",
			"/image.png/");
	}

	SECTION("url without port - http")
	{
		CHttpUrl url("http://testurl.ru/image.png/");
		CheckUrlProperties(url,
			"http://testurl.ru/image.png/",
			Protocol::HTTP,
			80,
			"testurl.ru",
			"/image.png/");
	}

	SECTION("url without port - https")
	{
		CHttpUrl url("https://testurl.ru/image.png/");
		CheckUrlProperties(url,
			"https://testurl.ru/image.png/",
			Protocol::HTTPS,
			443,
			"testurl.ru",
			"/image.png/");
	}

	SECTION("url with 0 port")
	{
		REQUIRE_THROWS_WITH(CHttpUrl("https://testurl.ru:0/image.png/"),
			"Port value 0 is out of range [1-65535]");
	}

	SECTION("url with 65536 port")
	{
		REQUIRE_THROWS_WITH(CHttpUrl("https://testurl.com:65536/image.png/"),
			"Port value 65536 is out of range [1-65535]");
	}

	SECTION("url with port 1")
	{
		CHttpUrl url("https://testurl.ru:1/image.png/");
		CheckUrlProperties(url,
			"https://testurl.ru:1/image.png/",
			Protocol::HTTPS,
			1,
			"testurl.ru",
			"/image.png/");
	}

	SECTION("url with port 65535")
	{
		CHttpUrl url("https://testurl.ru:65535/image.png/");
		CheckUrlProperties(url,
			"https://testurl.ru:65535/image.png/",
			Protocol::HTTPS,
			65535,
			"testurl.ru",
			"/image.png/");
	}

	SECTION("ip address")
	{
		CHttpUrl url("https://127.0.0.1:65535/image.png/");
		CheckUrlProperties(url,
			"https://127.0.0.1:65535/image.png/",
			Protocol::HTTPS,
			65535,
			"127.0.0.1",
			"/image.png/");
	}

	SECTION("Empty document") {
		CHttpUrl url("http://example.com");
		CheckUrlProperties(url,
			"http://example.com",
			Protocol::HTTP,
			80,
			"example.com",
			"/");
	}

	SECTION("Single slash document") {
		CHttpUrl url("http://example.com/");
		CheckUrlProperties(url,
			"http://example.com",
			Protocol::HTTP,
			80,
			"example.com",
			"/");
	}

	SECTION("Port with single slash document")
	{
		CHttpUrl url("https://test.com:8025/");
		CheckUrlProperties(url,
			"https://test.com:8025",
			Protocol::HTTPS,
			8025,
			"test.com",
			"/");
	}

	SECTION("Invalid domains") {
		REQUIRE_THROWS_WITH(CHttpUrl("http://-test.com"), "Invalid URL");
		REQUIRE_THROWS_WITH(CHttpUrl("http://test-.com"), "Invalid URL");
		REQUIRE_THROWS_WITH(CHttpUrl("http://test..com"), "Invalid URL");
		REQUIRE_THROWS_WITH(CHttpUrl("http://test--com"), "Invalid URL");
	}

	SECTION("invalid url in capital letters")
	{
		REQUIRE_THROWS_WITH(CHttpUrl("htt://invalidurl:8025/testdocument/"), "Invalid URL");
		REQUIRE_THROWS_WITH(CHttpUrl("https:/invalidurl:8025/testdocument/"), "Invalid URL");
		REQUIRE_THROWS_WITH(CHttpUrl("https:invalidurl:8025/testdocument/"), "Invalid URL");
		REQUIRE_THROWS_WITH(CHttpUrl("htt://invalid url"), "Invalid URL");
		REQUIRE_THROWS_WITH(CHttpUrl("htt://invalidurl:8025/test document/"), "Invalid URL");
	}
}

TEST_CASE("url constructor with 3 parameters")
{
	SECTION("url with domain and document, without Protocol")
	{
		CHttpUrl url("test.com", "image");
		CheckUrlProperties(url,
			"http://test.com/image",
			Protocol::HTTP,
			80,
			"test.com",
			"/image");
	}

	SECTION("url with domain, document and protocol")
	{
		CHttpUrl url("test.com", "/image.png", Protocol::HTTP);
		CheckUrlProperties(url,
			"http://test.com/image.png",
			Protocol::HTTP,
			80,
			"test.com",
			"/image.png");
	}

	SECTION("url with domain, document (long) and protocol")
	{
		CHttpUrl url("test.ru", "/path/to/document/", Protocol::HTTP);
		CheckUrlProperties(url,
			"http://test.ru/path/to/document/",
			Protocol::HTTP,
			80,
			"test.ru",
			"/path/to/document/");
	}
}

TEST_CASE("url constructor with 4 parameters")
{
	SECTION("url with domain, document, protocol, port")
	{
		CHttpUrl url("test.com", "path/to/image.png", Protocol::HTTP, 8080);
		CheckUrlProperties(url,
			"http://test.com:8080/path/to/image.png",
			Protocol::HTTP,
			8080,
			"test.com",
			"/path/to/image.png");
	}

	SECTION("url with domain, document, protocol, port (non-standard HTTPS - 80)")
	{
		CHttpUrl url("test.com", "/image.png", Protocol::HTTPS, 80);
		CheckUrlProperties(url,
			"https://test.com:80/image.png",
			Protocol::HTTPS,
			80,
			"test.com",
			"/image.png");
	}

	SECTION("url with domain, document, protocol, port (non-standard HTTP - 443)")
	{
		CHttpUrl url("test.com", "/image.png", Protocol::HTTP, 443);
		CheckUrlProperties(url,
			"http://test.com:443/image.png",
			Protocol::HTTP,
			443,
			"test.com",
			"/image.png");
	}

	SECTION("url with domain, document, protocol, port 0")
	{
		REQUIRE_THROWS_WITH(CHttpUrl("test.ru", "/path/to/document/", Protocol::HTTP, 0),
			"Port value 0 is out of range [1-65535]");
	}
}