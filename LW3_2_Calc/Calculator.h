#pragma once
#include "Operand.h"
#include <string>
#include <vector>
#include <memory>
#include <map>

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
	std::map<std::string, double> GetAllVariables() const;

	ErrorDescription GetErrorDescription() const;
	void SetErrorDescription(const ErrorDescription& er);

private:
	std::vector<std::unique_ptr<Operand>> m_operand;
	ErrorDescription m_errorDescription = ErrorDescription::NoError;
};

