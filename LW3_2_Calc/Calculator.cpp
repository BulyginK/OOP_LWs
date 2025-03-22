#include "Calculator.h"
#include <regex>

bool CCalculator::SetVar(const std::string& variable)
{
	if (!IsNameCorrect(variable))
	{
		return false;
	}
	if (!IsVarExist(variable))
	{
		return false;
	}
	m_variables.insert({ variable, std::numeric_limits<double>::quiet_NaN() }); //присваиваем var NaN
	// std::numeric_limits — это шаблонный класс из стандартной библиотеки C++, который предоставляет информацию о свойствах числовых типов (например, минимальное и максимальное значение, наличие NaN, точность и т.д.)
	return true;
};

double CCalculator::GetValue(const std::string& id) const
{
	if (m_variables.find(id) != m_variables.end())
	{
		return m_variables.at(id);
	}
	return std::numeric_limits<double>::quiet_NaN();
}

bool CCalculator::IsNameCorrect(const std::string& name)
{
	const std::regex reg("^[a-zA-Z_]{1}[_0-9a-zA-Z]*$");
	if (name.empty() || !regex_match(name, reg))
	{
		SetErrorDescription(ErrorDescription::InvalidUsage);
		return false;
	}
	return true;
}

bool CCalculator::IsVarExist(const std::string& variable)
{
	if (m_variables.find(variable) != m_variables.end())
	{
		SetErrorDescription(ErrorDescription::DuplicateName);
		return false;
	}
	return true;
}

ErrorDescription CCalculator::GetErrorDescription() const
{
	return m_errorDescription;
}

void CCalculator::SetErrorDescription(const ErrorDescription& errorDescription)
{
	m_errorDescription = errorDescription;
}