#pragma once
#include "Operand.h"
#include <string>
#include <vector>
#include <memory>
#include <map>
#include <optional>

enum class ErrorDescription
{
	UnknownCommand,
	InvalidUsage,
	DuplicateName,
	NoError
};

static const std::map<std::string, ErrorDescription> ERROR_DESCRIPRTION
{
	{ "Unknown command", ErrorDescription::UnknownCommand },
	{ "Invalid usage", ErrorDescription::InvalidUsage },
	{ "Name already exists", ErrorDescription::DuplicateName },
};

class CCalculator
{
public:
	bool DeclareVariable(const std::string& identifier);
	bool IsOperandDeclared(std::string identifier) const;
	
	bool SetVariableValue(std::string identifier, std::string newValue);
	
	std::map<std::string, double> GetAllVariables() const;

	ErrorDescription GetErrorDescription() const;
	void SetErrorDescription(const ErrorDescription& er);

private:
	std::optional<std::unique_ptr<Operand>*> GetOperandRef(std::string identifier);
	std::optional<double> DetermineNewValueOfVariable(const std::string& newValue);

	std::vector<std::unique_ptr<Operand>> m_operands;
	ErrorDescription m_errorDescription = ErrorDescription::NoError;
};

