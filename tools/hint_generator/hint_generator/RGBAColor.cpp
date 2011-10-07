#include "RGBAColor.h"

namespace higan
{
	const RGBAColor RGBAColor::White(255,255,255,255);
	const RGBAColor RGBAColor::Black(0,0,0,255);

	RGBAColor::RGBAColor(unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha):
	red(red),
	green(green),
	blue(blue),
	alpha(alpha)
	{
	}

	RGBAColor::RGBAColor(unsigned long ulongColor)
	{
		unsigned char* pColor = (unsigned char*)&ulongColor;
		red = pColor[0];
		green = pColor[1];
		blue = pColor[2];
		alpha = pColor[3];
	}

	unsigned long RGBAColor::to_ulong() const
	{
		unsigned char ulong[4] = { red, green, blue, alpha };
		return *((unsigned long*)ulong);
	}
}