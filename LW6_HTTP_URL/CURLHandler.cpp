#include <string>
#include "CURLHandler.h"
#include "CHttpUrl.h"
#include "CUrlParsingError.h"

CUrlHandler::CUrlHandler(std::istream& input, std::ostream& output)
	: m_input(input)
	, m_output(output)
{}

bool CUrlHandler::ParseAndExtractUrlDetails()
{
	std::string line;
	std::getline(m_input, line);
	if (line.empty())
	{
		return false;
	}
	try
	{
		CHttpUrl url(line);
		m_output << url.GetURL() << '\n';
		m_output << "PROTOCOL: "	<< GetProtocol(url.GetProtocol()) << '\n';
		m_output << "DOMAIN: "		<< url.GetDomain() << '\n';
		m_output << "PORT: "		<< url.GetPort() << '\n';
		m_output << "DOC: "			<< url.GetDocument() << '\n';
	}
	catch (CUrlParsingError const& exception)
	{
		m_output << exception.what() << '\n';
	}
	return true;
}

std::string CUrlHandler::GetProtocol(const Protocol& protocol)
{
	return (protocol == Protocol::HTTP ? "http" : "https");
}