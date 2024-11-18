#include <iostream>
#include <vector>
#include <string>
#include <Windows.h>
#include "Functions.h"

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	std::string path;
	std::vector<std::string> lines;
	ThreeDimensionalShape* ptr = nullptr;
	std::vector<std::string> results;
	std::cout << "Enter the path to the file: ";
	std::cin >> path;
	std::cin.get();
	try
	{
		lines = ReadFile(path);
		results = ProcessFile(lines, ptr);
		WriteFile(results);
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}	
	
	std::cout << "Press Enter to exit...";
	std::cin.get();

	return 0;
}