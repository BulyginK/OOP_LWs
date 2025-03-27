#include "Operand.h"
#include <regex>

bool COperand::IsCorrectIdentifier(const std::string& identifier)
{
	const std::regex r("^(?!_+$)[a-zA-Z_][_0-9a-zA-Z]*$");
	return regex_match(identifier, r);
}