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

    CFunctionExpression(const std::string& identifier, const std::string& operand1, const std::string& operand2, const std::string& signStr);

    OperandType COperand::GetType() const override;

    std::string GetIdentifier() const override;
    //std::string GetOperand1() const;
    //std::string GetOperand2() const;
    //Sign GetSign() const;


    static bool IsCorrectFunctionExpression(const std::string& expression);

private:
    const std::map<std::string, Sign> signes =
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