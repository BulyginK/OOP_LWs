#include "CHttpUrl.h"
#include <regex>
#include <iostream>

constexpr unsigned short DEFAULT_HTTP_PORT = 80;
constexpr unsigned short DEFAULT_HTTPS_PORT = 443;
constexpr unsigned short MIN_VALID_PORT = 1;
constexpr unsigned short MAX_VALID_PORT = 65535;

std::regex regexUrl(R"((http|https)://([0-9a-z]+(?:[.-][0-9a-z]+)*(?:\.[0-9a-z]+)+)(:([0-9]+))?(/([^\s]+)?)?)", std::regex::icase);
std::regex domainReg(R"(([0-9a-z\.-]+))", std::regex::icase);
std::regex documentReg(R"(([^\s]*))", std::regex::icase);

// не создавать parse url отдельно
CHttpUrl::CHttpUrl(const std::string& url)
{
	std::smatch matches;
	if (std::regex_match(url, matches, regexUrl))
	{
		Protocol protocol = matches[1].str() == "http" ? Protocol::HTTP : Protocol::HTTPS;
		Initialize(matches[2].str(), matches[6].str(), protocol, matches[4].str());
	}
	else
	{
		throw CUrlParsingError("Invalid URL");
	}
}

CHttpUrl::CHttpUrl(const std::string& domain, const std::string& document, Protocol protocol)
	: CHttpUrl(domain, document, protocol, (protocol == Protocol::HTTPS) ? DEFAULT_HTTPS_PORT : DEFAULT_HTTP_PORT)
{
}

CHttpUrl::CHttpUrl(const std::string& domain, const std::string& document, Protocol protocol, unsigned short port)
{
	Initialize(domain, document, protocol, std::to_string(port));
}

void CHttpUrl::Initialize(const std::string& domain, const std::string& document, Protocol protocol, const std::string& portStr)
{
	if (!std::regex_match(domain, domainReg) || !std::regex_match(document, documentReg))
	{
		throw std::invalid_argument("Invalid URL parameters");
	}

	m_protocol = protocol;
	m_domain = ToLowLetters(domain);

	m_document = ToLowLetters(document);

	if (m_document[0] != '/')
	{
		m_document.insert(0, "/");
	}

	m_port = GetPort(portStr, protocol);
}

std::string CHttpUrl::GetURL()const
{
	std::string protocol = m_protocol == Protocol::HTTPS ? "https://" : "http://";
	std::string port = ((m_port == DEFAULT_HTTPS_PORT && m_protocol == Protocol::HTTPS) || (m_port == DEFAULT_HTTP_PORT && m_protocol == Protocol::HTTP)) ? "" : (':' + std::to_string(m_port));
	std::string document = m_document == "/" ? "" : m_document;
	return protocol + m_domain + port + document;
}

unsigned short CHttpUrl::GetPort(const std::string& portStr, const Protocol protocol)
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

std::string CHttpUrl::GetProtocol(const Protocol protocol)
{
	return (protocol == Protocol::HTTP ? "http" : "https");
}

std::string ToLowLetters(const std::string& str)
{
	std::string strInLowLetters = str;
	std::transform(strInLowLetters.begin(), strInLowLetters.end(), strInLowLetters.begin(), tolower);
	return strInLowLetters;
}