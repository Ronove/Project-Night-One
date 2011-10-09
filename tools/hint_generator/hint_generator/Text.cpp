#include "Text.h"
#include "Font.h"

#include <cassert>
#include <SDL_ttf.h>
#include <string>
#include "SDL_gfxBlitFunc.h"

namespace higan
{
	Text::Text(const Font& font):
	font(font),
	width(0),
	height(0)
	{
		defaultSettings();
	}

	Text::Text(const Font& font, const std::string& text):
	font(font)
	{
		setText(text);
		defaultSettings();
	}

	void Text::defaultSettings()
	{
		encoding = LATIN1;
		renderMode = Solid;
	}

	Font Text::getFont() const
	{
		return font;
	}

	void Text::setText(const std::string& text)
	{
		std::string str = text;
		int lineSkip = font.getLineSkip(); // Get the line-skip value.
		width = height = 0;	
		
		// Break the String into its lines:
		int n = 0;
		while( n != -1 ) 
		{
			// Get until either '\n' or '\0':
			std::string strSub;
			n = str.find( '\n', 0 ); // Find the next '\n'
			strSub = str.substr( 0,n );
			if( n != -1 ) {
				str = str.substr( n+1, -1 );
			}
			this->text.push_back(strSub);

			// Get the size of the rendered text:
			int w = 0;
			getTextSize(UTF8, strSub, &w, &height );
			if( w > width ) {  width = w;  }
			// (really, we just want to see how wide this is going to be)
		}
		height = (this->text.size()-1) * lineSkip + height; // plus the first line	
	}
	
	void Text::setText(const std::vector<std::string> text)
	{
		this->text = text;
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
		fromRect(iRectangle(0,0,width,height),RGBAColor::Transparent);

		SDL_Surface* temp =0;

		for( unsigned i = 0; i < text.size(); ++i ) 
		{		
			switch(encoding)
			{
			case LATIN1:
				switch(renderMode)
				{
				case Solid:
					temp = TTF_RenderText_Solid(pFont,text[i].c_str(),*pColor);
					break;
				case Shaded:
					temp = TTF_RenderText_Shaded(pFont,text[i].c_str(),*pColor,*pShade);
					break;
				case Blended:
					temp = TTF_RenderText_Blended(pFont,text[i].c_str(),*pColor);
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
					temp = TTF_RenderUTF8_Solid(pFont,text[i].c_str(),*pColor);
					break;
				case Shaded:
					temp = TTF_RenderUTF8_Shaded(pFont,text[i].c_str(),*pColor,*pShade);
					break;
				case Blended:
					temp = TTF_RenderUTF8_Blended(pFont,text[i].c_str(),*pColor);
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
			
			// A surface should have been created by a non-empty string
			if(!text[i].empty())
			{
				assert(temp);
			}

			// Blit line to main surface
			SDL_Rect dstrect; dstrect.x = 0; dstrect.y = i * font.getLineSkip();
			SDL_gfxBlitRGBA( temp,NULL, surface, &dstrect);
			// Clean up:
			SDL_FreeSurface( temp );
			temp =0;
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

	void Text::getTextSize(Text::TextEncoding encoding, const std::string& text, int* width, int* height)
	{
		switch(encoding)
		{
		case LATIN1:
			font.getLATIN1Size(text,width,height);
			break;
		case UTF8:
			font.getUTF8Size(text,width,height);
			break;
		case UNICODE:
			font.getUNICODESize(text,width,height);
			break;
		default:
			assert(false);
			break;
		}
	}

	int Text::getWidth() const
	{
		return width;
	}

	int Text::getHeight() const
	{
		return height;
	}
}