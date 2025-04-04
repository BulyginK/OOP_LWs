#pragma once
#include <regex>

namespace 
{
    constexpr int DEFAULT_HTTP_PORT = 80;
    constexpr int DEFAULT_HTTPS_PORT = 443;
    constexpr int DEFAULT_FTP_PORT = 21;

    constexpr int MIN_VALID_PORT = 1;
    constexpr int MAX_VALID_PORT = 65535;
}


enum class Protocol
{
    HTTP,
    HTTPS,
    FTP
};

bool ParseURL(std::string const& url, Protocol& protocol, int& port, std::string& host, std::string& document);
bool GetProtocol(const std::string& str, Protocol& protocol);
int GetPort(const Protocol& protocol);  // если протокол не корректный - возврат -1
std::string ToLowLetters(const std::string& str);
