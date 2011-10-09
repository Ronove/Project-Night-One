#ifndef HIGAN_HINTGENERATOR_H
#define HIGAN_HINTGENERATOR_H

#include <string>

#include "Rectangle.h"
#include "Surface.h"

#include "BitmapGenerator.h"
#include "HintPageFactory.h"
#include "CSVReader.h"
#include "TextReader.h"
#include "Vector.h"

namespace higan
{
	class HintGenerator : public BitmapGenerator
	{
		std::string filename;
		higan::HintPageFactory pageFactory;
		higan::CSVReader csvReader;

		higan::pSurface createBitmap(const std::string& textinput);
	public:
		static const int ImageWidth;
		static const int ImageHeight;
		static const higan::iRectangle HintPageDimensions;
		static const Vector2i TopLeft;

		HintGenerator();
		void process();
	};
}

#endif