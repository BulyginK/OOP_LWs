#include "FunctionExpression.h"
#include <regex>

CFunctionExpression::CFunctionExpression(const std::string& identifier, const std::string& operand1, const std::string& operand2, const std::string& signStr)
	: m_identifier(identifier)
	, m_operand1(operand1)
	, m_operand2(operand2)
	, m_sign(GetSign(signStr))
{
};

CFunctionExpression::Sign CFunctionExpression::GetSign(std::string signStr)
{
	Sign s = Sign::Addition;
	for (auto sign : signes)
	{
		if (sign.first == signStr)
		{
			s = sign.second;
		}
	}
	return s;
}

bool CFunctionExpression::IsCorrectFunctionExpression(const std::string& expression)
{
	const std::regex reg(R"(^(?!_+$)[a-zA-Z_][_0-9a-zA-Z]*[-+*/]{1}(?!_+$)[a-zA-Z_][_0-9a-zA-Z]*$)");
    return regex_match(expression, reg);
}

std::string CFunctionExpression::GetIdentifier() const
{
    return m_identifier;
}

COperand::OperandType CFunctionExpression::GetType() const
{
    return OperandType::FunctionExpression;
}

