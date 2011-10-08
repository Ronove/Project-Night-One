#include "GraphicsContext.h"

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include <cassert>
#include "Screen.h"

namespace higan
{
	boost::scoped_ptr<GraphicsContext> GraphicsContext::pSingleton;

	GraphicsContext& GraphicsContext::getSingleton()
	{
		allocateSingleton();
		return *pSingleton;
	}

	GraphicsContext* GraphicsContext::getSingletonPtr()
	{
		allocateSingleton();
		return pSingleton.get();
	}
	
	void GraphicsContext::allocateSingleton()
	{
		if(!pSingleton)
		{
			pSingleton.reset(new GraphicsContext());
		}
	}

	GraphicsContext::GraphicsContext():
	pScreen(0)
	{
		if( SDL_Init(SDL_INIT_EVERYTHING) )
		{
			const char* error = SDL_GetError();
			assert(false);
		}

		unsigned long imginitflags = IMG_INIT_JPG|IMG_INIT_PNG|IMG_INIT_TIF;
		if( imginitflags != IMG_Init(imginitflags) )
		{
			const char* error = IMG_GetError();
			assert(false);
		}
		if( TTF_Init() )
		{
			const char* error = TTF_GetError();
			assert(false);
		}
	}

	GraphicsContext::~GraphicsContext()
	{
		delete pScreen;
		TTF_Quit();
		IMG_Quit();
		SDL_Quit();
	}

	void GraphicsContext::initScreen(int width, int height, const std::string& title, const RenderFormat& format)
	{
		if(pScreen)
		{
			delete pScreen;
			pScreen = 0;
		}

		pScreen = new Screen(width,height,title,format);
	}

	Screen* GraphicsContext::getScreen() const
	{
		return pScreen;
	}
}