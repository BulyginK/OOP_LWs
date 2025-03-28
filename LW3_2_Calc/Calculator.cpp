#include "Calculator.h"
#include "Variable.h"
#include "FunctionIdentifier.h"
#include "FunctionExpression.h"
#include <regex>
#include <charconv>

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

//Почему std::optional и std::nullopt ?
//Явное указание на отсутствие значения :
//В C++ нет аналога null для примитивных типов(например, double).
//std::optional решает эту проблему, позволяя вернуть либо число, либо "ничего".

std::optional<double> CCalculator::DetermineNewValueOfVariable(const std::string& newValue)
{
	double value = 0;
	const std::regex reg(R"(^-?\d+(?:\.\d+)?$)");
	if (regex_match(newValue, reg)) //это число
	{
		const char* str = newValue.c_str();
		auto [ptr, ec] = std::from_chars(str, str + newValue.size(), value);  
		// std::from_chars — функция из <charconv>, которая парсит строку в число без исключений 
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

std::map<std::string, double> CCalculator::GetAllOperands() const
{
	std::map <std::string, double> vars;
	for (auto& operand : m_operands)
	{
		if (operand->GetType() == COperand::OperandType::Variable)
		{
			vars[operand->GetIdentifier()] = static_cast<CVariable&>(*operand).GetValue();
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

std::string CCalculator::RemoveAllSpaces(std::string str) //стандартный способ удаления элементов по условию в C++
{
	str.erase(std::remove_if(str.begin(), str.end(),
		[](unsigned char c) { return std::isspace(c); }),
		str.end());
	return str;
}

bool CCalculator::GetOperandFunctionExpression(const std::string& identifier, const std::string& exprNoSpaces)
{
	const std::regex reg(R"([-+*/])");
	std::smatch match;
	if (std::regex_search(exprNoSpaces, match, reg))
	{
		const std::string sign = match[0];

		size_t signPos = exprNoSpaces.find(sign);
		unsigned int exprLen = exprNoSpaces.length();
		std::string operand1, operand2;
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
	return false;
}

// Объявляет новую функцию с ранее необъявленным именем <идентификатор1>
// результат применения одной из следующих бинарных операций к значениям ранее объявленных идентификаторов <идентификатор2> и <идентификатор3> в момент вычисления значения функции
bool CCalculator::DeclareFunction(const std::string& identifier, std::string expression)
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

	std::string exprNoSpaces = RemoveAllSpaces(expression); // Программа должна корректно распознавать операнды как в слитном виде, так и через пробел
	if (CFunctionExpression::IsCorrectFunctionExpression(exprNoSpaces)) //fn <идентификатор1> = <идентификатор2><операция><идентификатор3>
	{
		if (GetOperandFunctionExpression(identifier, exprNoSpaces))
		{
			return true;
		}

	}
	SetErrorDescription(ErrorDescription::IncorrectExpression);
	return false;
}

std::optional<double> CCalculator::CountValue(const std::string& identifier)
{
	if (IsOperandDeclared(identifier))
	{
		double res = 0;
		return Calculate(identifier, res);
	}
	else
	{
		SetErrorDescription(ErrorDescription::NameNotExist);
		return std::nullopt;
	}
}

double CCalculator::Calculate(const std::string& identifier, double& res)
{
	if (std::isnan(res))
	{
		return std::numeric_limits<double>::quiet_NaN();
	}

	for (auto& operand : m_operands)
	{
		if (operand->GetIdentifier() == identifier && operand->GetType() == COperand::OperandType::Variable)
		{
			CVariable& variable = static_cast<CVariable&>(*operand);  // *operand используется для разыменования умного указателя
			res = variable.GetValue();
			break;
		}
		if (operand->GetIdentifier() == identifier && operand->GetType() == COperand::OperandType::FunctionIdentifier)
		{
			CFunctionIdentifier& funIdentifier = static_cast<CFunctionIdentifier&>(*operand);  
			res = Calculate(funIdentifier.GetOperand(), res);
			break;
		}
		if (operand->GetIdentifier() == identifier && operand->GetType() == COperand::OperandType::FunctionExpression)
		{
			CFunctionExpression& expr = static_cast<CFunctionExpression&>(*operand);
			CFunctionExpression::Sign sign = expr.GetSign();
			double res1 = 0;
			res1 = Calculate(expr.GetOperand1(), res1);
			double res2 = 0;
			res2 = Calculate(expr.GetOperand2(), res2);
			if (sign == CFunctionExpression::Sign::Addition)
			{
				res = res1 + res2;
			}
			if (sign == CFunctionExpression::Sign::Subtraction)
			{
				res = res1 - res2;
			}
			if (sign == CFunctionExpression::Sign::Multiplication)
			{
				res = res1 * res2;
			}
			if (sign == CFunctionExpression::Sign::Division)
			{
				res = res1 / res2;
			}
			break;
		}
		SetErrorDescription(ErrorDescription::InvalidUsage);
		return std::numeric_limits<double>::quiet_NaN();
	}
	return res;
}
