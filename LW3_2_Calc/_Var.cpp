#include "Var.h"

	
CVar::CVar(const std::string& name, const double& value = nan(""))
	: m_name(name)
	, m_value(value)
{
}

std::string const CVar::GetName()
{
	return m_name;
}

double const CVar::GetValue()
{ 
	return m_value;
}

bool CVar::operator==(const CVar& rhs) const
{
	return m_name == rhs.m_name && m_value == rhs.m_value;
}

struct CVar::HashFunc
{
	size_t operator()(const CVar& v) const
	{
		size_t nameHash = std::hash<std::string>{}(v.m_name);
		size_t valueHash = std::hash<double>{}(v.m_value);
		return nameHash ^ (valueHash << 1);
	}
};