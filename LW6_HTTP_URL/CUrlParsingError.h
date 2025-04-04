#pragma once
#include <stdexcept>

// CUrlParsingError наследуется от std::invalid_argument
// std::invalid_argument — это стандартный класс исключений
// который, в свою очередь, инициализирует std::logic_error
class CUrlParsingError : public std::invalid_argument  
{
public:
    CUrlParsingError(const std::string& message);
};