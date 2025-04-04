#include "ParseURL.h"

std::string ToLowLetters(const std::string& str)
{
	std::string strInLowLetters = str;
	std::transform(strInLowLetters.begin(), strInLowLetters.end(), strInLowLetters.begin(), tolower);
	return strInLowLetters;
}

bool GetProtocol(const std::string& str, Protocol& protocol)
{
	std::string lowerStr = ToLowLetters(str);

	if (lowerStr == "http")
	{
		protocol = Protocol::HTTP;
		return true;
	}
	if (lowerStr == "https")
	{
		protocol = Protocol::HTTPS;
		return true;
	}
	if (lowerStr == "ftp")
	{
		protocol = Protocol::FTP;
		return true;
	}
	return false;
}

int GetPort(const Protocol& protocol)
{
	if (protocol == Protocol::HTTP)
	{
		return DEFAULT_HTTP_PORT;
	}
	if (protocol == Protocol::HTTPS)
	{
		return DEFAULT_HTTPS_PORT;
	}
	if (protocol == Protocol::FTP)
	{
		return DEFAULT_FTP_PORT;
	}
	return -1;
}

bool ParseURL(std::string const& url, Protocol& protocol, int& port, std::string& host, std::string& document)
{
	std::regex regexStr(R"((http|https|ftp)://([0-9a-z\.-]+)(:([0-9]+))?(/([^\s]+)?)?)", std::regex::icase);
	std::smatch result; // std::smatch, тип который представляет собой специализацию шаблонного класса std::match_results для строк типа std::string

	if (std::regex_match(url, result, regexStr))
	{
		if (!GetProtocol(result[1].str(), protocol)) {
			return false;
		}
		host = result[2].str();
		// Извлечение и проверка порта
		if (result[4].matched)
		{
			try {
				port = std::stoi(result[4].str());
				if (port < MIN_VALID_PORT || port > MAX_VALID_PORT)
				{
					return false;
				}
			}
			catch (const std::out_of_range&) {
				return false;
			}
		}
		else
		{
			port = GetPort(protocol);
			if (port < MIN_VALID_PORT || port > MAX_VALID_PORT)
			{
				return false;
			}
		}

		if (result[6].matched)
		{
			document = result[6].str();
		}
		// Если данных нет, document остается пустой строкой

		return true;
	}
	return false;
}

// R() - нет необходимости экранирования специальных символов
// () обозначают группу захвата
// [] обозначают класс символов
// ^ означает отрицание
// 
// \s — пробельным символам
//  К пробельным символам относятся :
//	Пробел().
//	Табуляция(\t).
//	Новая строка(\n).
//	Возврат каретки(\r).
//	Вертикальная табуляция(\v).
//	Перевод страницы(\f).
// 
//  * означает "ноль или более повторений предыдущего элемента".