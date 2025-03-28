#include "Calculator.h"
#include "RemoteControl.h"
#include <iostream>

int main()
{
	CCalculator calc;
	RemoteControl remoteControl(calc, std::cin, std::cout);
	while (!std::cin.eof() && !std::cin.fail())
	{
		std::cout << "> ";
		if (!remoteControl.HandleCommand())
		{
			std::cout << "Invalid command!" << std::endl;
		}
	}
	return 0;
}