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
	}

	void Bitmap::Paint(const iRectangle& rect, const RGBAColor& color)
	{
		SDL_Rect sdlrect = { (Sint16)rect.x, (Sint16)rect.y, (Uint16)rect.w, (Uint16)rect.h };
		SDL_FillRect(surface, &sdlrect, color.to_ulong());
	}
	
	void Bitmap::to_BMP(const std::string& filename)
	{
		if( !SDL_SaveBMP(surface,filename.c_str()) )
		{
			const char* error = SDL_GetError();
			assert(false);
		}
	}
}