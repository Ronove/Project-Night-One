#include "Font.h"

#include <cassert>
#include "Text.h"

namespace higan
{
	Font::Font()
	{
		defaultValues();
	}

	Font::Font(const std::string& file, int ptsize)
	{
		defaultValues();
		load(file,ptsize);
	}

	Font::Font(const Font& other)
	{
		*this = other;
	}

	Font& Font::operator=(const Font& other)
	{
		if(this != &other)
		{
			defaultValues();
			load(other.fontName,other.ptSize);
			setStyle(other.style);
			setOutline(other.outline);
			setHinting(other.hinting);
			setKerning(other.kerning);
		}

		return *this;
	}

	Font::~Font()
	{
		TTF_CloseFont(font);
	}

	void Font::defaultValues()
	{
		font = 0;
		fontName = "";
		ptSize = 0;
		style = NormalStyle;
		outline = 0;
		hinting = NormalHinting;
		kerning = false;
	}

	void Font::load(const std::string& file, int ptsize)
	{
		TTF_CloseFont(font);
		font = 0;

		font = TTF_OpenFont(file.c_str(),ptsize);
		if( !font )
		{
			const char* errorMsg = TTF_GetError();
			assert(false);
		}

		ptSize = ptsize;
		fontName = file;
	}

	std::string Font::getFontName() const
	{
		return fontName;
	}

	int Font::getPtSize() const
	{
		return ptSize;
	}

	void Font::setStyle(FontStyle style)
	{
		assert(font);
		TTF_SetFontStyle(font,style);
		this->style = style;
	}

	Font::FontStyle Font::getStyle() const
	{
		assert(font);
		return (FontStyle)TTF_GetFontStyle(font);
	}

	void Font::setOutline(int px)
	{
		assert(font);
		TTF_SetFontOutline(font,px);
		outline = px;
	}

	int Font::getOutline() const
	{
		assert(font);
		return TTF_GetFontOutline(font);
	}

	void Font::setHinting(FontHinting hinting)
	{
		assert(font);
		TTF_SetFontHinting(font,hinting);
		this->hinting = hinting;
	}

	Font::FontHinting Font::getHinting() const
	{
		assert(font);
		return (FontHinting)TTF_GetFontHinting(font);
	}

	void Font::setKerning(bool enabled)
	{
		assert(font);
		TTF_SetFontKerning(font,enabled);
		kerning = enabled;
	}

	bool Font::getKerning() const
	{
		assert(font);
		return TTF_GetFontKerning(font) ? true:false ;
	}

	int Font::getLineSkip() const
	{
		assert(font);
		return TTF_FontLineSkip(font);
	}

	void Font::getLATIN1Size(const std::string& text, int* width, int* height) const
	{
		TTF_SizeText(font,text.c_str(),width,height);
	}

	void Font::getUTF8Size(const std::string& text, int* width, int* height) const
	{
		TTF_SizeUTF8(font,text.c_str(),width,height);
	}

	void Font::getUNICODESize(const std::string& text, int* width, int* height) const
	{
		// Not supported
		assert(false);
		// TTF_SizeUNICODE(font,text.c_str(),width,height);
	}
}