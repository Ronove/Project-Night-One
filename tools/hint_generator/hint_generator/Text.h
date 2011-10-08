#ifndef HIGANTEXT_H
#define HIGANTEXT_H

#include "Font.h"
#include "Surface.h"
#include "RGBAColor.h"

namespace higan
{
	class Text : public Surface
	{
	public:
		Text();
		Text(const Font& font, const std::string& text="");

		void setFont(const Font& font);
		Font getFont() const;

		void setColor(const RGBAColor& color);
		RGBAColor getColor() const;

		void setShade(const RGBAColor& color);
		RGBAColor getShade() const;

		enum TextEncoding
		{
			LATIN1,
			UTF8,
			UNICODE,
		};

		void setEncoding(TextEncoding encoding);
		TextEncoding getEncoding() const;

		enum TextRenderMode
		{
			Solid,
			Shaded,
			Blended,
		};

		void setRenderMode(TextRenderMode rendermove);
		TextRenderMode getRenderMode() const;

	private:
		void prePaint();
		void postPaint();
		void prePainted();

		Font font;
		std::string text;
		RGBAColor color;
		RGBAColor shade;

		void defaultSettings();
		TextEncoding encoding;
		TextRenderMode renderMode;
	};
}

#endif