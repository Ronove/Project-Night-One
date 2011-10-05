#include "HintPageFactory.h"

#include "Rectangle.h"
#include "Bitmap.h"

namespace higan
{
	HintPageFactory::HintPageFactory(const iRectangle& dimensions):
	dimensions(dimensions)
	{
	}

	// TODO: Implement routine which creates the actual bitmap from text input
	pBitmap HintPageFactory::createBitmap(const std::string& textInputFilename)
	{
		return pBitmap();
	}
}