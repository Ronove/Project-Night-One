#include "HintPageFactory.h"

#include "Rectangle.h"
#include "Bitmap.h"
#include "RGBAColor.h"

namespace higan
{
	HintPageFactory::HintPageFactory(const iRectangle& dimensions):
	dimensions(dimensions)
	{
	}

	pBitmap HintPageFactory::createBitmap(const std::string& textInputFilename)
	{
		pBitmap bitmap(new Bitmap(dimensions));

		iRectangle firstHalf(0,0,dimensions.w/2,dimensions.h);
		iRectangle secondHalf(dimensions.w/2,0,dimensions.w/2,dimensions.h);

		bitmap->Paint(firstHalf,RGBAColor::Black);
		bitmap->Paint(secondHalf,RGBAColor::White);

		return bitmap;
	}
}