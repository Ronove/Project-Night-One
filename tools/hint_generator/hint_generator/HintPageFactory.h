#ifndef HIGAN_HINTPAGEFACTORY_H
#define HIGAN_HINTPAGEFACTORY_H

#include <string>

#include "Rectangle.h"
#include "Bitmap.h"

namespace higan
{
	class HintPageFactory
	{
	public:
		HintPageFactory(const iRectangle& dimensions);
		pBitmap createHintPage(const std::string& textInputFilename);
	};
}

#endif