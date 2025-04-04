#include <iostream>
#include "CURLHandler.h"

int main()
{
	CUrlHandler urlHandler(std::cin, std::cout);
	while (std::cin)
	{
		if (!urlHandler.ParseAndExtractUrlDetails())
		{
			std::cout << "Empty string" << std::endl;
		}
	}
	return 0;
}