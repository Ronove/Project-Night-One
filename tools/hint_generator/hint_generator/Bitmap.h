#ifndef HIGAN_BITMAP_H
#define HIGAN_BITMAP_H

#include <boost/shared_ptr.hpp>

#include <string>

#include "Rectangle.h"
#include "Surface.h"
#include "Text.h"
#include "Vector.h"

struct SDL_Surface;

namespace higan
{
	class RGBAColor;

	class Bitmap : public Surface
	{
	public:
		// Create bitmap from file
		Bitmap(const std::string& filename);
		// Create empty bitmap
		Bitmap(const iRectangle& rect);
		~Bitmap();
	};

	typedef boost::shared_ptr<Bitmap> pBitmap;
}

#endif