#ifndef HIGANSURFACE_H
#define HIGANSURFACE_H

#include <string>
#include <boost/shared_ptr.hpp>

#include "Vector.h"
#include "Rectangle.h"
#include "RGBAColor.h"

struct SDL_Surface;

namespace higan
{
	class Surface
	{
	public:
		Surface();
		~Surface();

		void setMemoryManaged(bool managed);
		bool getMemoryManaged() const;

		void fromRect(const iRectangle& rect, const RGBAColor& color);
		void fromFile(const std::string& filename);

		void blit(Surface& surface, const Vector2i& position);
		void blit(Surface& surface, const Vector2i& position, const iRectangle& clip);
		void paint(const iRectangle& rect, const RGBAColor& color);
		void to_BMP(const std::string& filename);

		void setAlpha(unsigned char alpha);
		unsigned char getAlpha() const;

		void setVisible(bool visible);
		bool getVisible() const;
	protected:
		virtual void prePaint(){};
		virtual void postPaint(){};
		virtual void prePainted(){};
		virtual void postPainted(){};

		SDL_Surface* surface;
		unsigned char alpha;
		bool managed;
	};
	
	typedef boost::shared_ptr<Surface> pSurface;
}
#endif