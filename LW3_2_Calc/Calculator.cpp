#include "Calculator.h"
#include "Variable.h"
#include <regex>
#include <charconv>

CCalculator::CCalculator() {};

// Объявляет переменную
bool CCalculator::DeclareVariable(const std::string& identifier)
{
	if (!COperand::IsCorrectIdentifier(identifier))
	{
		SetErrorDescription(ErrorDescription::InvalidUsage);
		return false;
	}
	if (IsOperandDeclared(identifier))
	{
		SetErrorDescription(ErrorDescription::DuplicateName);
		return false;
	}
	m_operands.emplace_back(std::make_unique<CVariable>(identifier));
	return true;
};

// Идентификатор не должен совпадать ни с одним из ранее объявленных имен переменных и функций
bool CCalculator::IsOperandDeclared(const std::string& identifier) const
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

// let <идентификатор1> = <число с плавающей запятой> либо let <идентификатор1> = <идентификатор2>
// Присваивает переменной с именем <идентификатор1> числовое значение, либо текущее значение ранее объявленного идентификатора с именем <идентификатор2>
// Если переменная с именем <идентификатор1> не была ранее объявлена, происходит объявление новой переменной.
// В качестве <идентификатора1> не может выступать имя функции.
bool CCalculator::SetVariableValue(std::string identifier, std::string newValue)
{
	if (!COperand::IsCorrectIdentifier(identifier))
	{
		SetErrorDescription(ErrorDescription::InvalidUsage);
		return false;
	}
	auto value = DetermineNewValueOfVariable(newValue);
	if (!value)
	{
		SetErrorDescription(ErrorDescription::NotNumberEntered);
		return false;
	}
	auto operandRef = GetOperandRef(identifier);
	if (!operandRef)
	{
		m_operands.emplace_back(std::make_unique<CVariable>(identifier, value.value())); 		// Если переменная не существует, создаем новую
		return true;
	}
	// Проверка типа операнда
	try {
		CVariable& variable = dynamic_cast<CVariable&>(operandRef->get());
		variable.SetValue(value.value());
		return true;
	}
	catch (const std::bad_cast&) {
		SetErrorDescription(ErrorDescription::InvalidUsage);
		return false;
	}
}

//std::unique_ptr<COperand>& CCalculator::GetOperandRef(std::string identifier)
//{
//	for (auto& var : m_operands)
//	{
//		if (var->GetIdentifier() == identifier)
//		{
//			return var;
//		}
//	}
//	static std::unique_ptr<COperand> notFound(nullptr);
//	return notFound;
//}

std::optional<std::reference_wrapper<COperand>> CCalculator::GetOperandRef(const std::string& identifier) const
{
	for (auto& var : m_operands)
	{
		if (var->GetIdentifier() == identifier)
		{
			return std::ref(*var);
		}
	}
	return std::nullopt;
}

std::optional<double> CCalculator::DetermineNewValueOfVariable(const std::string& newValue)
{
	double value = 0;
	//const std::regex reg(R"(^-{0,1}\d+(\.\d+){0,1}$)");
	const std::regex reg(R"(^-?\d+(?:\.\d+)?$)");
	if (regex_match(newValue, reg)) //это число
	{
		const char* str = newValue.c_str();
		auto [ptr, ec] = std::from_chars(str, str + newValue.size(), value);  // std::from_chars — функция из <charconv>, которая парсит строку в число без исключений 
		// ptr (const char*) — указатель на первый необработанный символ после числа
		// ec (std::errc) — код ошибки (аналог errno)

		if (ec == std::errc() && ptr == str + newValue.size())
			return value;
	}
	else //это идентификатор с корректным именем
	{
		return std::nullopt;
	}
}



std::map<std::string, double> CCalculator::GetAllVariables() const
{
	std::map <std::string, double> vars;
	for (auto& var : m_operands)
	{
		if (var->GetType() == COperand::OperandType::Variable)
		{
			vars[var->GetIdentifier()] = static_cast<CVariable&>(*var).GetValue();
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