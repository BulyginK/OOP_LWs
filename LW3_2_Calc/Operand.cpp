#include "Operand.h"
#include <regex>

bool Operand::IsCorrectIdentifier(const std::string& identifier)
{
	const std::regex r("^[a-zA-Z_]{1}[_0-9a-zA-Z]*$");
	return regex_match(identifier, r);
}