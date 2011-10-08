#include "Font.h"

#include <cassert>

namespace higan
{
	Font::Font():
	font(0)
	{
	}

	Font::Font(const std::string& file, int ptsize):
	font(0)
	{
		load(file,ptsize);
	}

	Font::~Font()
	{
		TTF_CloseFont(font);
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
	}

	void Font::setStyle(FontStyle style)
	{
		assert(font);
		TTF_SetFontStyle(font,style);
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
	}

	bool Font::getKerning() const
	{
		assert(font);
		return TTF_GetFontKerning(font);
	}
}