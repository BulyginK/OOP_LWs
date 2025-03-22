#pragma once
#include <string>
#include <unordered_set>

class CVar
{
	CVar(const std::string& name, const double& value = nan(""));

	std::string const GetName();
	double const GetValue();

private:
	const std::string m_name;
	double m_value;

	bool operator==(const CVar& rhs) const;

	struct HashFunc;
};