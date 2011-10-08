#include "HintPageFactory.h"

#include <string>

#include "Rectangle.h"
#include "Bitmap.h"
#include "RGBAColor.h"
#include "Font.h"
#include "Text.h"
#include "TextReader.h"
#include "HintGenerator.h"

namespace higan
{
	HintPageFactory::HintPageFactory(const iRectangle& pageDimensions):
	pageDimensions(pageDimensions),
	twoPageDimensions(pageDimensions.x,pageDimensions.y,pageDimensions.w*2,pageDimensions.h)
	{
	}

	pBitmap HintPageFactory::createBitmap(const std::string& textInput)
	{
		pBitmap bitmap(new Bitmap(twoPageDimensions));

		iRectangle firstHalf(0,0,twoPageDimensions.w/2,twoPageDimensions.h);
		iRectangle secondHalf(twoPageDimensions.w/2,0,twoPageDimensions.w/2,twoPageDimensions.h);

		bitmap->paint(firstHalf,RGBAColor::Black);
		bitmap->paint(secondHalf,RGBAColor::White);

		Font font("Arial.ttf",14);
		Text text(font,textInput);

		bitmap->blit(text,HintGenerator::TopLeft);

		return bitmap;
	}
}