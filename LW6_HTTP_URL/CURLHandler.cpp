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
		std::string protocol = url.GetProtocol() == Protocol::HTTPS ? "https" : "http";
		m_output << "Protocol: " << protocol << '\n';
		m_output << "Port: " << url.GetPort() << '\n';
		m_output << "Domain: " << url.GetDomain() << '\n';
		m_output << "Document: " << url.GetDocument() << '\n';
	}
	catch (CUrlParsingError const& exception)
	{
		m_output << exception.what() << '\n';
	}
	return true;
}