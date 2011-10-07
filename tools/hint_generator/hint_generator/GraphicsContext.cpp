#include "GraphicsContext.h"

#include <SDL.h>
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
	}

	GraphicsContext::~GraphicsContext()
	{
		delete pScreen;
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