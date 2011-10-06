#include <iostream>
#include <string>
#include <SDL_main.h>

#include "HintGenerator.h"

int main(int argc, char* argv[])
{
	try
	{
		if(argc != 2)
		{
			throw "Wrong number of arguments";
		}

		higan::HintGenerator hintGenerator(argv[1]);
		hintGenerator.process();
	}
	catch(char const* errorMsg)
	{
		std::cerr << "Fatal error: " << errorMsg << std::endl;
	}
	catch(const std::string& errorMsg)
	{
		std::cerr << "Fatal error: " << errorMsg << std::endl;
	}

	std::cout << "Program ended normally." << std::endl;

	return 0;
}