#include "Screen.h"

#include <SDL.h>
#include <string>

#include "GraphicsContext.h"

namespace higan
{
	Screen::Screen(int width, int height, const std::string& title, const GraphicsContext::RenderFormat& format)
	{
		unsigned long videoflags = 0;

		if(format == GraphicsContext::SOFTWARE)
		{
			videoflags |= SDL_SWSURFACE;
		}
		else if(format ==  GraphicsContext::HARDWARE)
		{
			videoflags |= SDL_HWSURFACE;
		}

		screen = SDL_SetVideoMode(width,height,32,videoflags);
		if(!screen)
			throw SDL_GetError();

		SDL_WM_SetCaption(title.c_str(),0);
	}

	unsigned long Screen::flags() const
	{
		return screen->flags;
	}

	unsigned char Screen::depth() const
	{
		return screen->format->BitsPerPixel;
	}

	unsigned long Screen::Rmask() const
	{
		return screen->format->Rmask;
	}

	unsigned long Screen::Gmask() const
	{
		return screen->format->Gmask;
	}

	unsigned long Screen::Bmask() const
	{
		return screen->format->Bmask;
	}

	unsigned long Screen::Amask() const
	{
		return screen->format->Amask;
	}

}