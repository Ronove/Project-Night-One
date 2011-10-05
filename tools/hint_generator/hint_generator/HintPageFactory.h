#ifndef HIGAN_HINTPAGEFACTORY_H
#define HIGAN_HINTPAGEFACTORY_H

#include <string>

#include "Rectangle.h"
#include "Bitmap.h"

namespace higan
{
	class HintPageFactory
	{
		iRectangle dimensions;
	public:
		HintPageFactory(const iRectangle& dimensions);
		pBitmap createBitmap(const std::string& textInputFilename);
	};
}

#endif