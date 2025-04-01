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
    // ��������� ������� ���������� ������������� URL-�, � ������ ������ ��������
    // ����������� ���������� CUrlParsingError, ���������� ��������� �������� ������
    CHttpUrl(std::string const& url);

    /* �������������� URL �� ������ ���������� ����������.
        ��� �������������� ������� ���������� ����������� ����������
        std::invalid_argument
        ���� ��� ��������� �� ���������� � ������� /, �� ��������� / � ����� ���������
    */
    CHttpUrl(
        std::string const& domain,
        std::string const& document,
        Protocol protocol = Protocol::HTTP);

    /* �������������� URL �� ������ ���������� ����������.
        ��� �������������� ������� ���������� ����������� ����������
        std::invalid_argument
        ���� ��� ��������� �� ���������� � ������� /, �� ��������� / � ����� ���������
    */
    CHttpUrl(
        std::string const& domain,
        std::string const& document,
        Protocol protocol,
        unsigned short port);

    // ���������� ��������� ������������� URL-�. ����, ���������� ����������� ���
    // ���������� ��������� (80 ��� http � 443 ��� https) � ��� ������
    // �� ������ ����������
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