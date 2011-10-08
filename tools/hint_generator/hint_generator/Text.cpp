#include "Text.h"
#include "Font.h"

#include <cassert>
#include <SDL_ttf.h>

namespace higan
{
	Text::Text()
	{
		defaultSettings();
	}

	Text::Text(const Font& font, const std::string& text):
	font(font),
	text(text)
	{
		defaultSettings();
	}

	void Text::defaultSettings()
	{
		encoding = LATIN1;
		renderMode = Solid;
	}

	void Text::setFont(const Font& font)
	{
		this->font = font;
	}

	Font Text::getFont() const
	{
		return font;
	}

	void Text::setColor(const RGBAColor& color)
	{
		this->color = color;
	}

	RGBAColor Text::getColor() const
	{
		return color;
	}

	void Text::setShade(const RGBAColor& shade)
	{
		this->shade = shade;
	}

	RGBAColor Text::getShade() const
	{
		return shade;
	}

	void Text::setEncoding(TextEncoding encoding)
	{
		this->encoding = encoding;
	}

	Text::TextEncoding Text::getEncoding() const
	{
		return encoding;
	}

	void Text::setRenderMode(TextRenderMode rendermode)
	{
		renderMode = rendermode;
	}

	Text::TextRenderMode Text::getRenderMode() const
	{
		return renderMode;
	}

	void Text::prePaint()
	{
		TTF_Font* pFont = font.font;
		SDL_Color* pColor = reinterpret_cast<SDL_Color*>(&color);
		SDL_Color* pShade = reinterpret_cast<SDL_Color*>(&shade);

		assert(!surface);

		switch(encoding)
		{
		case LATIN1:
			switch(renderMode)
			{
			case Solid:
				surface = TTF_RenderText_Solid(pFont,text.c_str(),*pColor);
				break;
			case Shaded:
				surface = TTF_RenderText_Shaded(pFont,text.c_str(),*pColor,*pShade);
				break;
			case Blended:
				surface = TTF_RenderText_Blended(pFont,text.c_str(),*pColor);
				break;
			default:
				assert(false);
				break;
			}
			break;
		case UTF8:
			switch(renderMode)
			{
			case Solid:
				surface = TTF_RenderUTF8_Solid(pFont,text.c_str(),*pColor);
				break;
			case Shaded:
				surface = TTF_RenderUTF8_Shaded(pFont,text.c_str(),*pColor,*pShade);
				break;
			case Blended:
				surface = TTF_RenderUTF8_Blended(pFont,text.c_str(),*pColor);
				break;
			default:
				assert(false);
				break;
			}
			break;
		case UNICODE:
			// NO.
			assert(false);
		default:
			assert(false);
		break;
		}

		if(!surface)
		{
			const char* errorMsg = TTF_GetError();
			assert(false);
		}
	}

	void Text::postPaint()
	{
		SDL_FreeSurface(surface);
		surface = 0;
	}
	
	void Text::prePainted()
	{
		// Unsupported operation
		assert(false);
	}
}