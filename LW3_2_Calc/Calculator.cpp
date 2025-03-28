#include "Calculator.h"
#include "Variable.h"
#include "FunctionIdentifier.h"
#include "FunctionExpression.h"
#include <regex>
#include <charconv>

//CCalculator::CCalculator() {};

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


bool CCalculator::ValidateIdentifier(const std::string& identifier)
{
	// Идентификатор должен соответствовать заданному условию 
	if (!COperand::IsCorrectIdentifier(identifier))
	{
		SetErrorDescription(ErrorDescription::InvalidUsage);
		return false;
	}
	// Идентификатор не должен совпадать ни с одним из ранее объявленных имен переменных и функций
	if (IsOperandDeclared(identifier))
	{
		SetErrorDescription(ErrorDescription::DuplicateName);
		return false;
	}
	return true;
}

// Объявляет переменную
bool CCalculator::DeclareVariable(const std::string& identifier)
{
	if (ValidateIdentifier(identifier))
	{
		m_operands.emplace_back(std::make_unique<CVariable>(identifier));
		return true;
	}
	return false;
};

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
	auto value = DetermineNewValueOfVariable(newValue);  // обработка присваиваемого значения
	if (!value)
	{
		// SetErrorDescription установлено ранее в DetermineNewValueOfVariable
		return false;
	}
	auto operandRef = GetOperandRef(identifier);
	if (!operandRef) // Если переменная не существует, создаем новую
	{
		m_operands.emplace_back(std::make_unique<CVariable>(identifier, value.value())); // можно вместо value.value() использовать разыменование *value, но не будет выбрасываться исключение std::bad_optional_access с понятным сообщением 	
		return true;
	}
	// если указан <идентификатор2>
	try {
		CVariable& variable = dynamic_cast<CVariable&>(operandRef->get()); // operandRef->get() возвращает ссылку COperand& из обертки reference_wrapper
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

std::optional<std::reference_wrapper<COperand>> CCalculator::GetOperandRef(const std::string& identifier) const  // reference_wrapper — это обёртка для ссылки
{
	for (auto& operand : m_operands)
	{
		if (operand->GetIdentifier() == identifier)
		{
			return std::ref(*operand);
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
		{
			return value;
		}
	}
	else if (!COperand::IsCorrectIdentifier(newValue))
	{
		SetErrorDescription(ErrorDescription::IncorrectIdentifier);
		return std::nullopt;
	}
	else // правый идентификатор с корректным именем
	{
		auto operandRef = GetOperandRef(newValue);

		if (!operandRef) //такого идентификатора не существует
		{
			SetErrorDescription(ErrorDescription::IncorrectIdentifier);
			return std::nullopt;
		}
		else // этот идентификатор существует
		{
			try {
				CVariable& variable = dynamic_cast<CVariable&>(operandRef->get());
				return variable.GetValue();
			}
			catch (const std::bad_cast&) {
				SetErrorDescription(ErrorDescription::InvalidUsage);
				return false;
			}
		}
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

std::string CCalculator::RemoveAllSpaces(std::string str)
{
	str.erase(std::remove_if(str.begin(), str.end(),
		[](unsigned char c) { return std::isspace(c); }),
		str.end());
	return str;
}

bool CCalculator::DeclareFunction(const std::string& identifier, std::string expression) // expression - выражение
{
	if (!ValidateIdentifier(identifier))
	{
		return false;
	}

	if (COperand::IsCorrectIdentifier(expression)) // если fn <идентификатор1> = <идентификатор2>
	{
		if (!IsOperandDeclared(expression))
		{
			SetErrorDescription(ErrorDescription::NameNotExist);
			return false;
		}
		m_operands.emplace_back(std::make_unique<CFunctionIdentifier>(identifier, expression));
		return true;
	}

	std::string exprNoSpaces = RemoveAllSpaces(expression);
	if (CFunctionExpression::IsCorrectFunctionExpression(exprNoSpaces)) //fn <идентификатор1> = <идентификатор2><операция><идентификатор3>
	{
		//const std::regex reg("[+\\-*\\/]");
		const std::regex reg(R"([-+*/])");
		std::smatch match;
		if (std::regex_search(exprNoSpaces, match, reg))
		{
			const std::string sign = match[0];

			size_t signPos = exprNoSpaces.find(sign);
			if (signPos != std::string::npos)
			{
				std::string operand1, operand2;
				unsigned int exprLen = exprNoSpaces.length();
				operand1.append(exprNoSpaces, 0, signPos);
				operand2.append(exprNoSpaces, signPos + 1, exprLen - signPos - 1);
				if (
					COperand::IsCorrectIdentifier(operand1) &&
					COperand::IsCorrectIdentifier(operand2) &&
					IsOperandDeclared(operand1) &&
					IsOperandDeclared(operand2)
					)
				{
					m_operands.emplace_back(std::make_unique<CFunctionExpression>(identifier, operand1, operand2, sign));
					return true;
				}
			}
		}

	}
	else
	{
		SetErrorDescription(ErrorDescription::IncorrectExpression);
		return false;
	}
}
