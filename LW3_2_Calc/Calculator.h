#pragma once
#include <string>
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
	CCalculator() = default;
	~CCalculator() = default;

	bool SetVar(const std::string& variable);
	double GetValue(const std::string& id) const;
	ErrorDescription GetErrorDescription() const;
	void SetErrorDescription(const ErrorDescription& er);

private:
	bool IsNameCorrect(const std::string& name);
	bool IsVarExist(const std::string& variable);

	std::map<std::string, double> m_variables;
	ErrorDescription m_errorDescription = ErrorDescription::NoError;
};

