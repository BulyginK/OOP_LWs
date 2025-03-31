#pragma once
#include <stdexcept>

// CUrlParsingError наследуетс€ от std::invalid_argument
// std::invalid_argument Ч это стандартный класс исключений
class CUrlParsingError : public std::invalid_argument  
{
public:
    //Е explicit
};