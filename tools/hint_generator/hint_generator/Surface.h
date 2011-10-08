#ifndef HIGANSURFACE_H
#define HIGANSURFACE_H

#include <string>

#include "Vector.h"
#include "Rectangle.h"
#include "RGBAColor.h"

struct SDL_Surface;

namespace higan
{
	class Surface
	{
	public:
		void blit(Surface& surface, const Vector2i& position);
		void blit(Surface& surface, const Vector2i& position, const iRectangle& clip);
		void paint(const iRectangle& rect, const RGBAColor& color);
		void to_BMP(const std::string& filename);

	protected:
		Surface();

		virtual void prePaint(){};
		virtual void postPaint(){};
		virtual void prePainted(){};
		virtual void postPainted(){};

		SDL_Surface* surface;
	};
}
#endif