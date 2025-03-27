#include "FunctionIdentifier.h"

CFunctionIdentifier::CFunctionIdentifier(std::string identifier, std::string operand)
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

