#pragma once
#include <istream>

class CUrlHandler
{
public:
	CUrlHandler(std::istream& input, std::ostream& output);
	bool ParseAndExtractUrlDetails();
private:
	std::istream& m_input;
	std::ostream& m_output;
}; 