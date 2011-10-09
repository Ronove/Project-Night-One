#ifndef HIGANFONT_H
#define HIGANFONT_H

#include <string>
#include <SDL_ttf.h>

namespace higan
{
	class Font
	{
	public:
		Font();
		Font(const std::string& file, int ptsize);
		Font(const Font& other);
		Font& operator=(const Font& other);

		~Font();

		friend class Text;

		void load(const std::string& file, int ptsize);
		std::string getFontName() const;
		int getPtSize() const;

		enum FontStyle
		{
			NormalStyle =		TTF_STYLE_NORMAL,
			Bold =				TTF_STYLE_BOLD,
			Italic =			TTF_STYLE_ITALIC,
			Underline =			TTF_STYLE_UNDERLINE,
			Strikethrough =		TTF_STYLE_STRIKETHROUGH,
		};

		void setStyle(FontStyle style);
		FontStyle getStyle() const;

		void setOutline(int px);
		int getOutline() const;

		enum FontHinting
		{
			NormalHinting =	TTF_HINTING_NORMAL,
			Light =			TTF_HINTING_LIGHT,
			Mono =			TTF_HINTING_MONO,
			None =			TTF_HINTING_NONE,
		};

		void setHinting(FontHinting hinting);
		FontHinting getHinting() const;

		void setKerning(bool enabled);
		bool getKerning() const;

		int getLineSkip() const;

		void getLATIN1Size(const std::string& text, int* width, int* height) const;
		void getUTF8Size(const std::string& text, int* width, int* height) const;
		void getUNICODESize(const std::string& text, int* width, int* height) const;

	protected:
		TTF_Font* font;

		void defaultValues();

		std::string fontName;
		int ptSize;
		FontStyle style;
		int outline;
		FontHinting hinting;
		bool kerning;
	};
}

#endif