#include "ShapeMenu.h"

int main(int, char*[])
{
	CShapeMenu menu;
	std::string command;
	try
	{
		while (std::getline(std::cin, command))
		{
			menu.ReadShape(command);
		}
		menu.PrintShapeMinPerimeter();
		menu.PrintShapeMaxArea();
		menu.PrintInfo();
		return 0;
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
	return 0;
}