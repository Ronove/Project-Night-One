#ifndef HIGAN_GRAPHICSCONTEXT_H
#define HIGAN_GRAPHICSCONTEXT_H

#include <boost/scoped_ptr.hpp>

#include <string>

#include "Bitmap.h"

struct SDL_Surface;

namespace higan
{
	class Screen;

	class GraphicsContext
	{
	public:
		enum RenderFormat
		{
			SOFTWARE,
			HARDWARE,
		};

		typedef unsigned long ScreenFormat;

		static GraphicsContext& getSingleton();
		static GraphicsContext* getSingletonPtr();

		void initScreen(int width, int height, const std::string& title, const RenderFormat& format);
		Screen* getScreen() const;

		~GraphicsContext();
	private:
		static void allocateSingleton();
		static boost::scoped_ptr<GraphicsContext> pSingleton;
		GraphicsContext();

		Screen* pScreen;
	};
}

#endif