#ifndef HIGAN_HINTPAGEFACTORY_H
#define HIGAN_HINTPAGEFACTORY_H

#include <string>

#include "Rectangle.h"
#include "Bitmap.h"

namespace higan
{
	class HintPageFactory
	{
		iRectangle pageDimensions;
		iRectangle twoPageDimensions;
	public:
		HintPageFactory(const iRectangle& pageDimensions);
		pBitmap createBitmap(const std::string& textInput);
	};
}

#endif