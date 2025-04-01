#include "CHttpUrl.h"
#include <regex>

std::regex regexUrl(R"((http|https)://([0-9a-z\.-]+)(:([0-9]+))?(/([^\s]+)?)?)", std::regex::icase);

CHttpUrl::CHttpUrl(std::string const& url)
{
	std::smatch matches;
	if (std::regex_match(url, matches, regexUrl))
	{
		m_protocol = matches[1].str() == "http" ? Protocol::HTTP : Protocol::HTTPS;
		std::string domain = matches[2].str();
		m_domain = ToLowLetters(domain);
		m_port = GetPort(matches[3].str(), m_protocol);
		std::string document = matches[4].str();
		m_document = document.empty() ? "/" : ToLowLetters(document);
	}
	else
	{
		throw CUrlParsingError("invalid url");
	}
}

unsigned short CHttpUrl::GetPort(const std::string& portStr, Protocol protocol)
{
	if (portStr.empty())
	{
		return protocol == Protocol::HTTP ? HTTP_PORT : HTTPS_PORT;
	}
	unsigned short port = std::stoi(portStr);
	if (port < MIN_PORT || port > MAX_PORT)
	{
		throw CUrlParsingError("invalid port value");
	}
	return port;
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