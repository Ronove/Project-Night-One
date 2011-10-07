#include <iostream>
#include <SDL_main.h>

#include "MainApp.h"

int main(int argc, char* argv[])
{
	higan::MainApp app(argc,argv);
	app.exec();

	std::cout << "Program ended normally." << std::endl;

	return 0;
}