#pragma once
#include <string>
#include "CUrlParsingError.h"


//namespace 
//{
//    constexpr unsigned short DEFAULT_HTTP_PORT = 80;
//    constexpr unsigned short DEFAULT_HTTPS_PORT = 443;
//
//    constexpr unsigned short MIN_VALID_PORT = 1;
//    constexpr unsigned short MAX_VALID_PORT = 65535;
//}


enum class Protocol
{
    HTTP,
    HTTPS
};


class CHttpUrl
{
public:
    // ��������� ������� ���������� ������������� URL-�, � ������ ������ ��������
    // ����������� ���������� CUrlParsingError, ���������� ��������� �������� ������
    CHttpUrl(std::string const& url);

    /* �������������� URL �� ������ ���������� ����������.
        ��� �������������� ������� ���������� ����������� ����������
        std::invalid_argument
        ���� ��� ��������� �� ���������� � ������� /, �� ��������� / � ����� ���������
    */
    //CHttpUrl(
    //    std::string const& domain,
    //    std::string const& document,
    //    Protocol protocol = Protocol::HTTP);

    /* �������������� URL �� ������ ���������� ����������.
        ��� �������������� ������� ���������� ����������� ����������
        std::invalid_argument
        ���� ��� ��������� �� ���������� � ������� /, �� ��������� / � ����� ���������
    */
    //CHttpUrl(
    //    std::string const& domain,
    //    std::string const& document,
    //    Protocol protocol,
    //    unsigned short port);

    // ���������� ��������� ������������� URL-�. ����, ���������� ����������� ���
    // ���������� ��������� (80 ��� http � 443 ��� https) � ��� ������
    // �� ������ ����������
    std::string GetURL() const;
    //Protocol GetProtocol(const std::string& str);

    std::string GetDomain() const;
    std::string GetDocument() const;
    Protocol GetProtocol() const;
    unsigned short GetPort() const;

    
private:
    static constexpr unsigned short DEFAULT_HTTP_PORT = 80;
    static constexpr unsigned short DEFAULT_HTTPS_PORT = 443;
    static constexpr unsigned short MIN_VALID_PORT = 1;
    static constexpr unsigned short MAX_VALID_PORT = 65535;

    unsigned short GetPort(const std::string& portStr, Protocol protocol);
    static std::string ToLowLetters(const std::string& str);

    std::string m_domain;
    Protocol m_protocol;
    unsigned short m_port;
    std::string m_document;
};