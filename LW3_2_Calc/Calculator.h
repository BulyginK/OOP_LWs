#pragma once
#include <string>
#include <map>

class CCalculator
{
	CCalculator();

	bool SetVar(const std::string& variable);


private:
	std::map<std::string, double> m_variables;
};

