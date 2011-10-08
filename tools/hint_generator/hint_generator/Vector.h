#ifndef HIGANVECTOR_H
#define HIGANVECTOR_H

namespace higan
{
	template<class T>
	class Vector2
	{
	public:
		Vector2(T x, T y):
		x(x),
		y(y)
		{
		}

		template<class K>
		Vector2(const Vector2<K>& v):
		x(v.x),
		y(v.y)
		{
		}

		T x;
		T y;
	};

	typedef Vector2<int>	Vector2i;
	typedef Vector2<float>	Vector2f;
}

#endif