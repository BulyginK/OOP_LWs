#pragma once
#include "Operand.h"
#include <string>
#include <vector>
#include <memory>
#include <map>
#include <optional>
#include <algorithm> 
#include <cctype>  

enum class ErrorDescription
{
	UnknownCommand,		// Если введена неизвестная команда
	InvalidUsage,		// Если синтаксис введенной команды не удовлетворяет правилам (в том числе недопустимый идентификатор)
	DuplicateName,		// Если переменная с таким именем уже была объявлена
	NameNotExist,		// Если в команде используется необъявленная переменная
	NotNumberEntered,	// Если присваивается не число
	IncorrectIdentifier,
	IncorrectExpression,
	NoError			
};

static const std::map<std::string, ErrorDescription> ERROR_DESCRIPRTION
{
	{ "Unknown command", ErrorDescription::UnknownCommand },
	{ "Invalid usage", ErrorDescription::InvalidUsage },
	{ "Name already exists", ErrorDescription::DuplicateName },
	{ "Name does not exist", ErrorDescription::NameNotExist },
	{ "Not a number entered", ErrorDescription::NotNumberEntered},
	{ "Incorrect identifier", ErrorDescription::IncorrectIdentifier },
	{ "Incorrect expression", ErrorDescription::IncorrectExpression }
};

class CCalculator
{
public:
	CCalculator() = default;

	bool DeclareVariable(const std::string& identifier);
	bool DeclareFunction(const std::string& identifier, std::string expression);

	

	bool IsOperandDeclared(const std::string& identifier) const;
	
	bool SetVariableValue(std::string identifier, std::string newValue);
	
	std::map<std::string, double> GetAllVariables() const;

	ErrorDescription GetErrorDescription() const;
	void SetErrorDescription(const ErrorDescription& er);
	std::optional<std::reference_wrapper<COperand>> GetOperandRef(const std::string& identifier) const;
	std::optional<double> DetermineNewValueOfVariable(const std::string& newValue);

private:
	bool ValidateIdentifier(const std::string& identifier);
	std::string RemoveAllSpaces(std::string str);


	std::vector<std::unique_ptr<COperand>> m_operands;  // std::unique_ptr тк нужны гетерогенные объекты - полиморфизм через указатели
	ErrorDescription m_errorDescription = ErrorDescription::NoError;
};

// для тестов вынесены в public
//std::unique_ptr<COperand>& GetOperandRef(std::string identifier);
//std::optional<double> DetermineNewValueOfVariable(const std::string& newValue);

//std::optional<std::unique_ptr<COperand>*> GetOperandRef(const std::string& identifier);
//std::optional<COperand*> GetOperandRef(const std::string& identifier) const;

//std::unique_ptr<COperand>& GetOperandRef(std::string identifier);
