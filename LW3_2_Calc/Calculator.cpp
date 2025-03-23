#include "Calculator.h"
#include "Variable.h"
#include <regex>

bool CCalculator::DeclareVariable(const std::string& identifier)
{
	if (!Operand::IsCorrectIdentifier(identifier))
	{
		SetErrorDescription(ErrorDescription::InvalidUsage);
		return false;
	}
	if (IsOperandDeclared(identifier))
	{
		SetErrorDescription(ErrorDescription::DuplicateName);
		return false;
	}
	m_operands.emplace_back(std::make_unique<Variable>(identifier));
	return true;
};

bool CCalculator::IsOperandDeclared(std::string identifier) const
{
	for (auto& operand : m_operands)
	{
		if (operand->GetIdentifier() == identifier)
		{
			return true;
		}
	}
	return false;
}



std::optional<std::unique_ptr<Operand>*> CCalculator::GetOperandRef(std::string identifier)
{
	for (auto& operand : m_operands)
	{
		if (operand->GetIdentifier() == identifier)
		{
			return &operand;
		}
	}
	return std::nullopt; // Элемент не найден
}

std::optional<double> CCalculator::DetermineNewValueOfVariable(const std::string& newValue)
{
	double value = 0;
	const std::regex reg(R"(^-{0,1}\d+(\.\d+){0,1}$)");
	if (regex_match(newValue, reg)) //это число
	{
		value = stod(newValue);
	}
	// TODO
}

bool CCalculator::SetVariableValue(std::string identifier, std::string newValue)
{
	if (!Operand::IsCorrectIdentifier(identifier))
	{
		SetErrorDescription(ErrorDescription::InvalidUsage);
		return false;
	}
	auto value = DetermineNewValueOfVariable(newValue);
	// TODO
}

std::map<std::string, double> CCalculator::GetAllVariables() const
{
	std::map <std::string, double> vars;
	for (auto& var : m_operands)
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