#include <fstream>
#include <string>
#include <cassert>

#include "HintGenerator.h"
#include "GraphicsContext.h"
#include "Rectangle.h"
#include "HintPageFactory.h"
#include "Surface.h"
#include "Vector.h"
#include "Screen.h"
#include "Timer.h"
#include "Font.h"
#include "Text.h"

namespace higan
{	
	const int higan::HintGenerator::ImageWidth = 472;
	const int higan::HintGenerator::ImageHeight = 386;
	const iRectangle higan::HintGenerator::HintPageDimensions = iRectangle(0,0,ImageWidth/2,ImageHeight);
	const Vector2i higan::HintGenerator::TopLeft = Vector2i(18,73);

	HintGenerator::HintGenerator():
	filename("dataset.csv"),
	pageFactory(HintPageDimensions)
	{
		GraphicsContext::getSingleton().initScreen(ImageWidth,ImageHeight,"Higanbana Hint Generator",GraphicsContext::SOFTWARE);
	}

	higan::pSurface HintGenerator::createBitmap(const std::string& textinput)
	{
		return pageFactory.createBitmap(textinput);
	}

	void HintGenerator::process()
	{
		csvReader.openFile( "config/" + filename);
		Screen& screen = *GraphicsContext::getSingleton().getScreen();
		while(csvReader.hasMoreRows())
		{
			std::vector<std::string> currentLine = csvReader.getRow();

			if(currentLine.size() < 2)
			{
				std::string error = "Invalid row size in csv file: " + filename + ". Should be [text input filename, bitmap output filename].";
				assert(false);
			}
			
			std::string textInput = TextReader::fileToString( "input/" + currentLine.at(0));
			higan::pSurface bitmap = createBitmap(textInput);

			screen.blit(*bitmap,Vector2i(0,0));			
			screen.flip();

			bitmap->to_BMP( "output/" + currentLine.at(1));
		}

		csvReader.closeFile();
	}
}