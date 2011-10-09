#ifndef HIGANRGBACOLOR_H
#define HIGANRGBACOLOR_H

namespace higan
{
	class RGBAColor
	{
	public:
		RGBAColor(unsigned char red=255, unsigned char green=255, unsigned char blue=255, unsigned char alpha=255);
		RGBAColor(unsigned long ulongColor);

		unsigned char red;
		unsigned char green;
		unsigned char blue;
		unsigned char alpha;

		unsigned long to_ulong() const;

		static const RGBAColor Transparent;
		static const RGBAColor White;
		static const RGBAColor Black;
		static const RGBAColor Red;
	};
}
#endif