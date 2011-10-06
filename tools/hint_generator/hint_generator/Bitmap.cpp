#include "Bitmap.h"

#include <SDL_image.h>

#include "GraphicsContext.h"
#include "Screen.h"

namespace higan
{
	Bitmap::Bitmap(const std::string& filename)
	{
		surface = IMG_Load(filename.c_str());

		if(!surface)
			throw IMG_GetError();
	}

	Bitmap::Bitmap(const iRectangle& rect)
	{
		const Screen& screen = *GraphicsContext::getSingleton().getScreen();

		surface = SDL_CreateRGBSurface(screen.flags(),rect.w,rect.h,screen.depth(),screen.Rmask(),screen.Gmask(),screen.Bmask(),screen.Amask());

		if(!surface)
			throw SDL_GetError();
	}

	Bitmap::~Bitmap()
	{
		SDL_FreeSurface(surface);
	}
}