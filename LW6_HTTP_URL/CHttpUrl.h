#pragma once
#include <string>
#include "CUrlParsingError.h"


namespace 
{
    constexpr int HTTP_PORT = 80;
    constexpr int HTTPS_PORT = 443;

    constexpr int MIN_PORT = 1;
    constexpr int MAX_PORT = 65535;
}


enum class Protocol
{
    HTTP,
    HTTPS
};


class CHttpUrl
{
public:
    // выполн€ет парсинг строкового представлени€ URL-а, в случае ошибки парсинга
    // выбрасывает исключение CUrlParsingError, содержащее текстовое описание ошибки
    CHttpUrl(std::string const& url);

    /* инициализирует URL на основе переданных параметров.
        ѕри недопустимости входных параметров выбрасывает исключение
        std::invalid_argument
        ≈сли им€ документа не начинаетс€ с символа /, то добавл€ет / к имени документа
    */
    CHttpUrl(
        std::string const& domain,
        std::string const& document,
        Protocol protocol = Protocol::HTTP);

    /* инициализирует URL на основе переданных параметров.
        ѕри недопустимости входных параметров выбрасывает исключение
        std::invalid_argument
        ≈сли им€ документа не начинаетс€ с символа /, то добавл€ет / к имени документа
    */
    CHttpUrl(
        std::string const& domain,
        std::string const& document,
        Protocol protocol,
        unsigned short port);

    // возвращает строковое представление URL-а. ѕорт, €вл€ющийс€ стандартным дл€
    // выбранного протокола (80 дл€ http и 443 дл€ https) в эту строку
    // не должен включатьс€
    std::string GetURL() const;
    Protocol GetProtocol(const std::string& str);

    std::string GetDomain() const;
    std::string GetDocument() const;
    Protocol GetProtocol() const;
    unsigned short GetPort() const;

    
private:
    unsigned short GetPort(const std::string& portStr, Protocol protocol);
    static std::string ToLowLetters(const std::string& str);

    std::string m_domain;
    Protocol m_protocol;
    unsigned short m_port;
    std::string m_document;

};