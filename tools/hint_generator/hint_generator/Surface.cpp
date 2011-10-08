#include "Surface.h"

#include <SDL.h>
#include <cassert>

#include "RGBAColor.h"

namespace higan
{
	Surface::Surface():
	surface(0)
	{
	}
	
	void Surface::blit(Surface& surface, const Vector2i& position)
	{
		prePainted();
		surface.prePaint();

		SDL_Rect pos; pos.x = position.x; pos.y = position.y;
		
		SDL_BlitSurface(surface.surface, 0, this->surface, &pos);

		postPainted();
		surface.postPaint();
	}

	void Surface::blit(Surface& surface, const Vector2i& position, const iRectangle& clip)
	{
		prePainted();
		surface.prePaint();
	
		SDL_Rect sdlclip; sdlclip.x = clip.x; sdlclip.y = clip.y; sdlclip.w = clip.w; sdlclip.h = clip.h;
		SDL_Rect pos; pos.x = position.x; pos.y = position.y;
		
		SDL_BlitSurface(surface.surface, &sdlclip, this->surface, &pos);

		postPainted();
		surface.postPaint();
	}

	void Surface::paint(const iRectangle& rect, const RGBAColor& color)
	{
		SDL_Rect sdlrect = { (Sint16)rect.x, (Sint16)rect.y, (Uint16)rect.w, (Uint16)rect.h };
		SDL_FillRect(surface, &sdlrect, color.to_ulong());
	}

	void Surface::to_BMP(const std::string& filename)
	{
		if( SDL_SaveBMP(surface,filename.c_str()) )
		{
			const char* error = SDL_GetError();
			assert(false);
		}
	}

}