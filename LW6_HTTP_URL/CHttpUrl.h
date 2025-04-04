#pragma once
#include <string>
#include "CUrlParsingError.h"

enum class Protocol
{
    HTTP,
    HTTPS
};

class CHttpUrl
{
public:
    CHttpUrl(std::string const& url);
    CHttpUrl(
        std::string const& domain,
        std::string const& document,
        Protocol protocol = Protocol::HTTP);
    CHttpUrl(
        std::string const& domain,
        std::string const& document,
        Protocol protocol,
        unsigned short port);

    std::string GetURL() const;
    std::string GetDomain() const;
    std::string GetDocument() const;
    Protocol GetProtocol() const;
    unsigned short GetPort() const;


    static std::string GetProtocol(const Protocol protocol);
    
private:

    void ParseUrl(const std::string& url);
    void Initialize(const std::string& domain, const std::string& document, Protocol protocol, const std::string& portStr);
    unsigned short GetPort(const std::string& portStr, const Protocol protocol);
    

    std::string m_domain;
    Protocol m_protocol;
    unsigned short m_port;
    std::string m_document;
};

static std::string ToLowLetters(const std::string& str);