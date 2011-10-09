#include "Screen.h"

#include <SDL.h>
#include <string>

#include "GraphicsContext.h"

namespace higan
{
	Screen::Screen(int width, int height, const std::string& title, const GraphicsContext::RenderFormat& format):
	Surface()
	{
		setMemoryManaged(false);

		unsigned long videoflags = 0;

		if(format == GraphicsContext::SOFTWARE)
		{
			videoflags |= SDL_SWSURFACE;
		}
		else if(format ==  GraphicsContext::HARDWARE)
		{
			videoflags |= SDL_HWSURFACE;
		}

		surface = SDL_SetVideoMode(width,height,32,videoflags);
		if(!surface)
		{
			const char* error = SDL_GetError();
			assert(false);
		}

		SDL_WM_SetCaption(title.c_str(),0);
	}

	void Screen::flip()
	{
		SDL_Flip(surface);
	}

	unsigned long Screen::flags() const
	{
		return surface->flags;
	}

	unsigned char Screen::depth() const
	{
		return surface->format->BitsPerPixel;
	}

	unsigned long Screen::Rmask() const
	{
		return surface->format->Rmask;
	}

	unsigned long Screen::Gmask() const
	{
		return surface->format->Gmask;
	}

	unsigned long Screen::Bmask() const
	{
		return surface->format->Bmask;
	}

	unsigned long Screen::Amask() const
	{
		return surface->format->Amask;
	}

}