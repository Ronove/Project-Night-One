#include "HintPageFactory.h"

#include <string>

#include "Rectangle.h"
#include "Surface.h"
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

	pSurface HintPageFactory::createBitmap(const std::string& textInput)
	{
		pSurface bitmap(new Surface());
		bitmap->fromRect(twoPageDimensions,RGBAColor::White);

		iRectangle firstHalf(0, 0, twoPageDimensions.w/2, twoPageDimensions.h);
		iRectangle secondHalf(twoPageDimensions.w/2, 0, twoPageDimensions.w/2, twoPageDimensions.h);

		bitmap->paint(firstHalf, RGBAColor::Black);
		bitmap->paint(secondHalf, RGBAColor::White);

		std::string fontName = TextReader::fileToString("config/fontToUse.txt");

		Font leftFont( "font/" + fontName,14);
		Text leftText(leftFont, textInput);
		leftText.setEncoding(Text::UTF8);
		leftText.setRenderMode(Text::Blended);
		bitmap->blit(leftText, HintGenerator::TopLeft);

		Font rightFont( "font/" + fontName,14);
		//rightFont.setOutline(5); TODO: Fix
		Text rightText(rightFont, textInput);
		rightText.setColor(RGBAColor::Black);
		rightText.setEncoding(Text::UTF8);
		rightText.setRenderMode(Text::Blended);

		// Stupid way of doing glow
		bitmap->blit(rightText, HintGenerator::TopLeft + Vector2i(secondHalf.x, secondHalf.y));
		bitmap->blit(rightText, HintGenerator::TopLeft + Vector2i(secondHalf.x+1, secondHalf.y));
		bitmap->blit(rightText, HintGenerator::TopLeft + Vector2i(secondHalf.x-1, secondHalf.y));
		bitmap->blit(rightText, HintGenerator::TopLeft + Vector2i(secondHalf.x, secondHalf.y+1));
		bitmap->blit(rightText, HintGenerator::TopLeft + Vector2i(secondHalf.x, secondHalf.y-1));

		return bitmap;
	}
}