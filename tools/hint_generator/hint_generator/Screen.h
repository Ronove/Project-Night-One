#ifndef HIGAN_SCREEN_H
#define HIGAN_SCREEN_H

#include <string>

#include "GraphicsContext.h"
#include "Surface.h"

struct SDL_Surface;

namespace higan
{
	class Screen : public Surface
	{
	public:
		friend class GraphicsContext;
		
		void flip();

		unsigned long flags() const;
		unsigned char depth() const;
		unsigned long Rmask() const;
		unsigned long Gmask() const;
		unsigned long Bmask() const;
		unsigned long Amask() const;

	private:
		Screen(int width, int height, const std::string& title, const GraphicsContext::RenderFormat& format);
	};
}

#endif