#include "Surface.h"

#include <SDL.h>
#include <SDL_image.h>
#include <cassert>
#include "SDL_gfxBlitFunc.h"

#include "RGBAColor.h"
#include "GraphicsContext.h"
#include "Screen.h"

namespace higan
{
	Surface::Surface():
	surface(0),
	managed(true),
	alpha(SDL_ALPHA_OPAQUE)
	{
	}

	Surface::~Surface()
	{
		if(managed)
		{
			SDL_FreeSurface(surface);
		}
		surface = 0;
	}

	void Surface::setMemoryManaged(bool managed)
	{
		this->managed = managed;
	}

	bool Surface::getMemoryManaged() const
	{
		return managed;
	}

	void Surface::fromRect(const iRectangle& rect, const RGBAColor& color)
	{
		const Screen& screen = *GraphicsContext::getSingleton().getScreen();

		SDL_Surface* temp = SDL_CreateRGBSurface(screen.flags(),rect.w,rect.h,screen.depth(),screen.Rmask(),screen.Gmask(),screen.Bmask(),screen.Amask());
		surface = SDL_DisplayFormatAlpha(temp);
		SDL_FreeSurface(temp);

		SDL_FillRect(surface,0,SDL_MapRGBA(surface->format, color.red, color.green, color.blue, color.alpha));
		setAlpha(color.alpha);

		if(!surface)
		{
			const char* error = SDL_GetError();
			assert(false);
		}
	}

	void Surface::fromFile(const std::string& filename)
	{
		surface = IMG_Load(filename.c_str());

		if(!surface)
		{
			const char* error = IMG_GetError();
			assert(false);
		}
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
		Surface temp;
		temp.fromRect(rect,color);
		blit(temp,Vector2i(rect.x,rect.y));
	}

	void Surface::to_BMP(const std::string& filename)
	{
		if( SDL_SaveBMP(surface,filename.c_str()) )
		{
			const char* error = SDL_GetError();
			assert(false);
		}
	}

	void Surface::setAlpha(unsigned char alpha)
	{
		this->alpha = alpha;
	}

	unsigned char Surface::getAlpha() const
	{
		return alpha;
	}

	void Surface::setVisible(bool visible)
	{
		setAlpha( visible ? SDL_ALPHA_OPAQUE : SDL_ALPHA_TRANSPARENT );
	}

	bool Surface::getVisible() const
	{
		return alpha != SDL_ALPHA_TRANSPARENT;
	}
}