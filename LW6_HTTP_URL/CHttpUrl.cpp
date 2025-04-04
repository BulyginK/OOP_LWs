#include "CHttpUrl.h"
#include <regex>
#include <iostream>

std::regex regexUrl(R"((http|https)://([0-9a-z]+(?:[.-][0-9a-z]+)*(?:\.[0-9a-z]+)+)(:([0-9]+))?(/([^\s]+)?)?)", std::regex::icase);
//std::regex regexUrl(R"((http|https)://([0-9a-z]+\.[a-z]{2,})(:([0-9]+))?(/([^\s]+)?)?)", std::regex::icase);
std::regex domainReg(R"(([0-9a-z\.-]+))", std::regex::icase);
std::regex documentReg(R"(([^\s]+))", std::regex::icase);

CHttpUrl::CHttpUrl(std::string const& url)
{
	std::smatch matches;
	if (std::regex_match(url, matches, regexUrl))
	{
		m_protocol = matches[1].str() == "http" ? Protocol::HTTP : Protocol::HTTPS;
		std::string domain = matches[2].str();
		m_domain = ToLowLetters(domain);
		m_port = GetPort(matches[4].str(), m_protocol);
		std::string document = matches[6].str();
		m_document = "/" + ToLowLetters(document);
	}
	else
	{
		throw CUrlParsingError("Invalid URL");
	}
}

CHttpUrl::CHttpUrl(std::string const& domain, std::string const& document, Protocol protocol)
	: m_protocol(protocol)
{
	if (std::regex_match(domain, domainReg) && std::regex_match(document, documentReg))
	{
		m_domain = ToLowLetters(domain);
		m_document = ToLowLetters(document);
		if (m_document[0] != '/')
		{
			m_document.insert(0, std::string("/"));
		}
		m_port = m_protocol == Protocol::HTTPS ? 443 : 80;
	}
	else
	{
		throw std::invalid_argument("invalid url parameters");
	}
}

CHttpUrl::CHttpUrl(std::string const& domain, std::string const& document, Protocol protocol, unsigned short port)
	: m_protocol(protocol)
{
	if (std::regex_match(domain, domainReg) && std::regex_match(document, documentReg))
	{
		m_domain = ToLowLetters(domain);
		m_document = ToLowLetters(document);
		if (m_document[0] != '/')
		{
			m_document.insert(0, std::string("/"));
		}
		m_port = GetPort(std::to_string(port), m_protocol);
	}
	else
	{
		throw std::invalid_argument("invalid url parameters");
	}
}

std::string CHttpUrl::GetURL()const
{
	std::string protocol = m_protocol == Protocol::HTTPS ? "https://" : "http://";
	std::string port = ((m_port == 443 && m_protocol == Protocol::HTTPS) || (m_port == 80 && m_protocol == Protocol::HTTP)) ? "" : (':' + std::to_string(m_port));
	std::string document = m_document == "/" ? "" : m_document;
	return protocol + m_domain + port + document;
}

unsigned short CHttpUrl::GetPort(const std::string& portStr, const Protocol& protocol)
{
	if (portStr.empty())
	{
		return protocol == Protocol::HTTP ? DEFAULT_HTTP_PORT : DEFAULT_HTTPS_PORT;
	}
	try {
		unsigned int port = std::stoul(portStr);
		if (port < MIN_VALID_PORT || port > MAX_VALID_PORT)
		{
			throw CUrlParsingError(
				"Port value " + portStr + " is out of range [" +
				std::to_string(MIN_VALID_PORT) + "-" +
				std::to_string(MAX_VALID_PORT) + "]");
		}
		return static_cast<unsigned short>(port);
	}
	catch (const std::out_of_range&) {
		throw CUrlParsingError("Port value is too large");
	}
}

std::string CHttpUrl::GetDomain() const
{
	return m_domain;
}

std::string CHttpUrl::GetDocument() const
{
	return m_document;
}

Protocol CHttpUrl::GetProtocol() const
{
	return m_protocol;
}

unsigned short CHttpUrl::GetPort() const
{
	return m_port;
}

std::string CHttpUrl::ToLowLetters(const std::string& str)
{
	std::string strInLowLetters = str;
	std::transform(strInLowLetters.begin(), strInLowLetters.end(), strInLowLetters.begin(), tolower);
	return strInLowLetters;
}