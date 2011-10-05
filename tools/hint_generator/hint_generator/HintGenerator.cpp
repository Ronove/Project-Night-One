#include <fstream>
#include <string>

#include "HintGenerator.h"
#include "Rectangle.h"
#include "HintPageFactory.h"
#include "Bitmap.h"
#include "BitmapSaver.h"

namespace higan
{	
	const int higan::HintGenerator::ImageWidth = 472;
	const int higan::HintGenerator::ImageHeight = 386;
	const iRectangle higan::HintGenerator::HintPageDimensions = iRectangle(0,0,ImageWidth/2,ImageHeight);

	HintGenerator::HintGenerator(const std::string& inputFilename):
	filename(inputFilename),
	pageFactory(HintPageDimensions)
	{
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
				throw "Invalid row size in csv file: " + filename + ". Should be [text input filename, bitmap output filename].";
			}

			std::string textInput = textReader.fileToString(currentLine.at(0));
			higan::pBitmap bitmap = createBitmap(textInput);
			bitmapSaver.saveBitmapToFile(bitmap,currentLine.at(1));
		}

		csvReader.closeFile();
	}
}