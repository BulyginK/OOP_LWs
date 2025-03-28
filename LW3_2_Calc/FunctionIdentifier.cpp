#include "FunctionIdentifier.h"

CFunctionIdentifier::CFunctionIdentifier(std::string const& identifier, std::string const& operand)
    : m_identifier(identifier)
    , m_operand(operand)
{
};

std::string CFunctionIdentifier::GetIdentifier() const
{
    return m_identifier;
}

COperand::OperandType CFunctionIdentifier::GetType() const
{
    return OperandType::FunctionIdentifier;
}

std::string CFunctionIdentifier::GetOperand() const
{
    return m_operand;
}