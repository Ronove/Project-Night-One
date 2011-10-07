#include <fstream>
#include <string>
#include <cassert>

#include "HintGenerator.h"
#include "GraphicsContext.h"
#include "Rectangle.h"
#include "HintPageFactory.h"
#include "Bitmap.h"

namespace higan
{	
	const int higan::HintGenerator::ImageWidth = 472;
	const int higan::HintGenerator::ImageHeight = 386;
	const iRectangle higan::HintGenerator::HintPageDimensions = iRectangle(0,0,ImageWidth/2,ImageHeight);

	HintGenerator::HintGenerator(const std::string& inputFilename):
	filename(inputFilename),
	pageFactory(HintPageDimensions)
	{
		GraphicsContext::getSingleton().initScreen(ImageWidth,ImageHeight,"Higanbana Hint Generator",GraphicsContext::SOFTWARE);
	}

	higan::pBitmap HintGenerator::createBitmap(const std::string& textinput)
	{
		return pageFactory.createBitmap(textinput);
	}

	void HintGenerator::process()
	{
		csvReader.openFile(filename);

		while(csvReader.hasMoreRows())
		{
			std::vector<std::string> currentLine = csvReader.getRow();

			if(currentLine.size() != 2)
			{
				std::string error = "Invalid row size in csv file: " + filename + ". Should be [text input filename, bitmap output filename].";
				assert(false);
			}

			std::string textInput = textReader.fileToString(currentLine.at(0));
			higan::pBitmap bitmap = createBitmap(textInput);
			bitmap->to_BMP(currentLine.at(1));
		}

		csvReader.closeFile();
	}
}