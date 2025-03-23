#include "Calculator.h"
#include "Variable.h"
#include <regex>

bool CCalculator::DeclareVariable(const std::string& identifier)
{
	if (IsOperandDeclared(identifier))
	{
		SetErrorDescription(ErrorDescription::DuplicateName);
		return false;
	}
	if (!Operand::IsCorrectIdentifier(identifier))
	{
		SetErrorDescription(ErrorDescription::InvalidUsage);
		return false;
	}
	m_operand.emplace_back(std::make_unique<Variable>(identifier));
	return true;
};

bool CCalculator::IsOperandDeclared(std::string identifier) const
{
	for (auto& operand : m_operand)
	{
		if (operand->GetIdentifier() == identifier)
		{
			return true;
		}
	}
	return false;
}

std::map<std::string, double> CCalculator::GetAllVariables() const
{
	std::map <std::string, double> vars;
	for (auto& var : m_operand)
	{
		if (var->GetType() == Operand::OperandType::Variable)
		{
			vars[var->GetIdentifier()] = static_cast<Variable&>(*var).GetValue();
		}
	}
	return vars;
}

ErrorDescription CCalculator::GetErrorDescription() const
{
	return m_errorDescription;
}

void CCalculator::SetErrorDescription(const ErrorDescription& errorDescription)
{
	m_errorDescription = errorDescription;
}