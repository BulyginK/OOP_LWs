#include "Variable.h"

Variable::Variable(std::string identifier, double value)
    : m_identifier(identifier)
    , m_value(value)
{
};

std::string Variable::GetIdentifier() const
{
    return m_identifier;
}

double Variable::GetValue() const
{
    return m_value;
}

void Variable::SetValue(double value)
{
    m_value = value;
}

Operand::OperandType Variable::GetType() const
{
    return OperandType::Variable;
}