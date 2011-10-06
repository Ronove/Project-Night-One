#ifndef HIGAN_BITMAP_H
#define HIGAN_BITMAP_H

#include <boost/shared_ptr.hpp>
#include <string>

#include "Rectangle.h"

class SDL_Surface;

namespace higan
{
	class Bitmap
	{
	public:
		// Create bitmap from file
		Bitmap(const std::string& filename);
		// Create empty bitmap
		Bitmap(const iRectangle& rect);

		~Bitmap();
	protected:
		SDL_Surface* surface;
	};

	typedef boost::shared_ptr<Bitmap> pBitmap;
}

#endif