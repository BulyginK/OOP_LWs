#include "FunctionExpression.h"
#include <regex>

CFunctionExpression::CFunctionExpression(std::string const& identifier, std::string const& operand1, std::string const& operand2, std::string const& signStr)
	: m_identifier(identifier)
	, m_operand1(operand1)
	, m_operand2(operand2)
	, m_sign(GetSign(signStr))
{
};

CFunctionExpression::Sign CFunctionExpression::GetSign(const std::string& signStr)
{
	Sign s = Sign::Addition;
	for (auto sign : m_signes)
	{
		if (sign.first == signStr)
		{
			s = sign.second;
		}
	}
	return s;
}

bool CFunctionExpression::IsCorrectFunctionExpression(const std::string& exprNoSpaces)
{
	const std::regex reg(R"(^(?!_+$)[a-zA-Z_][_0-9a-zA-Z]*[-+*/]{1}(?!_+$)[a-zA-Z_][_0-9a-zA-Z]*$)");
    return regex_match(exprNoSpaces, reg);
}

std::string CFunctionExpression::GetIdentifier() const
{
    return m_identifier;
}

COperand::OperandType CFunctionExpression::GetType() const
{
    return OperandType::FunctionExpression;
}

CFunctionExpression::Sign CFunctionExpression::GetSign() const
{
	return m_sign;
}

std::string CFunctionExpression::GetOperand1() const
{
	return m_operand1;
}

std::string CFunctionExpression::GetOperand2() const
{
	return m_operand2;
}

