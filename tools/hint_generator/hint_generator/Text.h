#ifndef HIGANTEXT_H
#define HIGANTEXT_H

#include "Font.h"
#include "Surface.h"
#include "RGBAColor.h"

#include <vector>

namespace higan
{
	class Text : public Surface
	{
	public:
		Text(const Font& font);
		Text(const Font& font, const std::string& text="");

		Font getFont() const;

		void setText(const std::string& text);
		void setText(const std::vector<std::string> text);

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

		void getTextSize(TextEncoding encoding, const std::string& text, int* width, int* height);

		int getWidth() const;
		int getHeight() const;

	private:
		void prePaint();
		void postPaint();
		void prePainted();

		const Font& font;
		std::vector<std::string> text;

		RGBAColor color;
		RGBAColor shade;

		void defaultSettings();

		TextEncoding encoding;
		TextRenderMode renderMode;
		int width;
		int height;
	};
}

#endif