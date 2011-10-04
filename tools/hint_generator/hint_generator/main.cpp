#include <SDL.h>
#include <SDL_main.h>
#include <SDL_ttf.h>

#include <fstream>
#include <string>
#include <boost/lexical_cast.hpp>

#include "Rectangle.h"
#include "HintPageFactory.h"
#include "Bitmap.h"
#include "BitmapSaver.h"

int main(int argc, char* argv[])
{
	if(argc != 2)
	{
		return -1;
	}

	std::ifstream inputFile(argv[1]);

	const higan::iRectangle hintPageDimensions(0,0,472/2,386);

	higan::HintPageFactory pageFactory(hintPageDimensions);
	higan::BitmapSaver bitmapSaver;

	while(!inputFile.eof())
	{
		std::string currentLine;
		std::getline(inputFile,currentLine);

		higan::pBitmap currentBitmap = pageFactory.createHintPage(currentLine);
		// TODO: grab output filenames from a csv table
		// bitmapSaver.SaveBitmapToFile(currentBitmap, OUTPUT_FILE_NAME_HERE);
	}

	bitmapSaver.SaveLog("hint_generator_log.txt");

	return 0;
}