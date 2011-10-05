#ifndef HIGAN_RECTANGLE_H
#define HIGAN_RECTANGLE_H

namespace higan
{

	template <class T>
	struct Rectangle
	{
		Rectangle(const T& x, const T& y, const T& w, const T& h):
		x(x),
		y(y),
		w(w),
		h(h)
		{	}

		template<class K>
		Rectangle(const Rectangle<K>& other)
		{
			x = other.x;
			y = other.y;
			w = other.w;
			h = other.h;
		}

		T x;
		T y;
		T w;
		T h;
	};

	typedef Rectangle<int>	 iRectangle;
	typedef Rectangle<float> fRectangle;
}

#endif