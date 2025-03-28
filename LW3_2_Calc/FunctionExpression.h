#pragma once
#include "Operand.h"
#include <string>
#include <map>

class CFunctionExpression final :
    public COperand
{
public:
    enum class Sign
    {
        Addition,
        Subtraction,
        Multiplication,
        Division
    };

    CFunctionExpression(std::string const& identifier, std::string const& operand1, std::string const& operand2, std::string const& signStr);

    OperandType COperand::GetType() const override;
    std::string GetIdentifier() const override;
    Sign GetSign() const;
    std::string GetOperand1() const;
    std::string GetOperand2() const;

    static bool IsCorrectFunctionExpression(const std::string& exprNoSpaces);

private:
    const std::map<std::string, Sign> m_signes =
    {
        {"+", Sign::Addition},
        {"-", Sign::Subtraction},
        {"*", Sign::Multiplication},
        {"/", Sign::Division}
    };
    Sign GetSign(std::string signStr);

    std::string m_identifier;
    std::string m_operand1;
    std::string m_operand2;
    Sign m_sign;
};