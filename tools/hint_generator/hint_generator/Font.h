#ifndef HIGANFONT_H
#define HIGANFONT_H

#include <string>
#include <SDL_ttf.h>

namespace higan
{
	class Font
	{
	protected:
		TTF_Font* font;
	public:
		Font();
		Font(const std::string& file, int ptsize);
		~Font();

		friend class Text;

		void load(const std::string& file, int ptsize);

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
	};
}

#endif