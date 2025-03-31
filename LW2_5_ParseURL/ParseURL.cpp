#include "ParseURL.h"

bool GetProtocol(const std::string& str, Protocol& protocol)
{
	std::string lowerStr = str;
	std::transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), ::tolower);

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
		return HTTP_PORT;
	}
	if (protocol == Protocol::HTTPS)
	{
		return HTTPS_PORT;
	}
	if (protocol == Protocol::FTP)
	{
		return FTP_PORT;
	}
	return -1;
}

bool ParseURL(std::string const& url, Protocol& protocol, int& port, std::string& host, std::string& document)
{
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
				if (port < MIN_PORT || port > MAX_PORT)
				{
					return false;
				}
			}
			catch (const std::invalid_argument&) {
				return false;
			}
			catch (const std::out_of_range&) {
				return false;
			}
		}
		else
		{
			port = GetPort(protocol);
			if (port < MIN_PORT || port > MAX_PORT)
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