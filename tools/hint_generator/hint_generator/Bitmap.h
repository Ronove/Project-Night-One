#ifndef HIGAN_BITMAP_H
#define HIGAN_BITMAP_H

#include <boost/shared_ptr.hpp>

#include <string>

#include "Rectangle.h"

struct SDL_Surface;

namespace higan
{
	class RGBAColor;

	class Bitmap
	{
	public:
		// Create bitmap from file
		Bitmap(const std::string& filename);
		// Create empty bitmap
		Bitmap(const iRectangle& rect);
		~Bitmap();

		void Paint(const iRectangle& rect, const RGBAColor& color);
		
		void to_BMP(const std::string& filename);
	protected:
		SDL_Surface* surface;
	};

	typedef boost::shared_ptr<Bitmap> pBitmap;
}

#endif