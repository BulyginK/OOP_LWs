#include "Variable.h"

CVariable::CVariable(std::string const& identifier, double const& value)
    : m_identifier(identifier)
    , m_value(value)
{
};

std::string CVariable::GetIdentifier() const
{
    return m_identifier;
}

double CVariable::GetValue() const
{
    return m_value;
}

void CVariable::SetValue(double value)
{
    m_value = value;
}

COperand::OperandType CVariable::GetType() const
{
    return OperandType::Variable;
}