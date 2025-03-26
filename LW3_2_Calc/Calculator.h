#pragma once
#include "Operand.h"
#include <string>
#include <vector>
#include <memory>
#include <map>
#include <optional>

enum class ErrorDescription
{
	UnknownCommand,		// Если введена неизвестная команда
	InvalidUsage,		// Если синтаксис введенной команды не удовлетворяет правилам (в том числе недопустимый идентификатор)
	DuplicateName,		// Если переменная с таким именем уже была объявлена
	NameNotExist,		// Если в команде используется необъявленная переменная
	NotNumberEntered,	// Если присваивается не число
	IncorrectIdentifier,
	NoError			
};

static const std::map<std::string, ErrorDescription> ERROR_DESCRIPRTION
{
	{ "Unknown command", ErrorDescription::UnknownCommand },
	{ "Invalid usage", ErrorDescription::InvalidUsage },
	{ "Name already exists", ErrorDescription::DuplicateName },
	{ "Name does not exist", ErrorDescription::NameNotExist },
	{ "Not a number entered", ErrorDescription::NotNumberEntered},
	{ "Incorrect identifier", ErrorDescription::IncorrectIdentifier }
};

class CCalculator
{
public:
	CCalculator();

	bool DeclareVariable(const std::string& identifier);
	bool DeclareFunction(const std::string& identifier, const std::string& expression);

	bool CheckIdentifier(const std::string& identifier);

	bool IsOperandDeclared(const std::string& identifier) const;
	
	bool SetVariableValue(std::string identifier, std::string newValue);
	
	std::map<std::string, double> GetAllVariables() const;

	ErrorDescription GetErrorDescription() const;
	void SetErrorDescription(const ErrorDescription& er);
	//std::unique_ptr<COperand>& GetOperandRef(std::string identifier);
	std::optional<std::reference_wrapper<COperand>> GetOperandRef(const std::string& identifier) const;
	std::optional<double> DetermineNewValueOfVariable(const std::string& newValue);

private:
	// для тестов вынесены в pablic
	//std::unique_ptr<COperand>& GetOperandRef(std::string identifier);
	//std::optional<double> DetermineNewValueOfVariable(const std::string& newValue);
	
	//std::optional<std::unique_ptr<COperand>*> GetOperandRef(const std::string& identifier);
	//std::optional<COperand*> GetOperandRef(const std::string& identifier) const;
	

	std::vector<std::unique_ptr<COperand>> m_operands;
	ErrorDescription m_errorDescription = ErrorDescription::NoError;
};

