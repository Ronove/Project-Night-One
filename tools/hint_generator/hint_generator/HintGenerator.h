#ifndef HIGAN_HINTGENERATOR_H
#define HIGAN_HINTGENERATOR_H

#include <string>

#include "Rectangle.h"
#include "Bitmap.h"

#include "HintPageFactory.h"
#include "BitmapSaver.h"
#include "CSVReader.h"
#include "TextReader.h"

namespace higan
{
	struct HintData
	{
		std::string textInput;
		std::string outputFilename;
	};

	class HintGenerator
	{
		std::string filename;
		higan::HintPageFactory pageFactory;
		higan::BitmapSaver bitmapSaver;
		higan::CSVReader csvReader;
		higan::TextReader textReader;

		higan::pBitmap createBitmap(const std::string& textinput);
	public:
		static const int ImageWidth;
		static const int ImageHeight;
		static const higan::iRectangle HintPageDimensions;

		HintGenerator(const std::string& inputFilename);
		void process();
	};
}

#endif