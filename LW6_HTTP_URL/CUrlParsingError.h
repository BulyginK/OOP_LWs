#pragma once
#include <stdexcept>

// CUrlParsingError наследуется от std::invalid_argument
// std::invalid_argument — это стандартный класс исключений
class CUrlParsingError : public std::invalid_argument  // который, в свою очередь, инициализирует std::logic_error
{
public:
    CUrlParsingError(const std::string& message);
};