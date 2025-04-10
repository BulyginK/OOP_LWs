﻿#include "ParseURL.h"
#include <iostream>

int main()
{
	std::string url;
	Protocol protocol;
	int port;
	std::string host;
	std::string document;

	while (std::getline(std::cin, url))
	{
		if (ParseURL(url, protocol, port, host, document))
		{
			std::cout << url << std::endl;
			std::cout << "HOST: " << host << std::endl;
			std::cout << "PORT: " << port << std::endl;
			std::cout << "DOC: " << document << std::endl;
		}
		else
		{
			std::cout << "ERROR" << std::endl;
			return 0;
		}
	}
	return 0;
}