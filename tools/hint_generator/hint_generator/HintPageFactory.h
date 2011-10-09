#ifndef HIGAN_HINTPAGEFACTORY_H
#define HIGAN_HINTPAGEFACTORY_H

#include <string>

#include "Rectangle.h"
#include "Surface.h"

namespace higan
{
	class HintPageFactory
	{
		iRectangle pageDimensions;
		iRectangle twoPageDimensions;
	public:
		HintPageFactory(const iRectangle& pageDimensions);
		pSurface createBitmap(const std::string& textInput);
	};
}

#endif