#ifndef HIGAN_SCREEN_H
#define HIGAN_SCREEN_H

#include <string>

#include "GraphicsContext.h"

struct SDL_Surface;

namespace higan
{
	class Screen
	{
	public:
		friend class GraphicsContext;

		unsigned long flags() const;
		unsigned char depth() const;
		unsigned long Rmask() const;
		unsigned long Gmask() const;
		unsigned long Bmask() const;
		unsigned long Amask() const;

	private:
		Screen(int width, int height, const std::string& title, const GraphicsContext::RenderFormat& format);
		SDL_Surface* screen;
	};
}

#endif