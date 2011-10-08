#include "Bitmap.h"

#include <SDL_image.h>
#include <cassert>

#include "GraphicsContext.h"
#include "RGBAColor.h"
#include "Rectangle.h"
#include "Screen.h"

namespace higan
{
	Bitmap::Bitmap(const std::string& filename)
	{
		surface = IMG_Load(filename.c_str());

		if(!surface)
		{
			const char* error = IMG_GetError();
			assert(false);
		}
	}

	Bitmap::Bitmap(const iRectangle& rect)
	{
		const Screen& screen = *GraphicsContext::getSingleton().getScreen();

		surface = SDL_CreateRGBSurface(screen.flags(),rect.w,rect.h,screen.depth(),screen.Rmask(),screen.Gmask(),screen.Bmask(),screen.Amask());

		if(!surface)
		{
			const char* error = SDL_GetError();
			assert(false);
		}
	}

	Bitmap::~Bitmap()
	{
		SDL_FreeSurface(surface);
		surface = 0;
	}
}