#ifndef HIGAN_BITMAPSAVER_H
#define HIGAN_BITMAPSAVER_H

#include <string>
#include <list>
#include <utility>

#include "Bitmap.h"

namespace higan
{
	class BitmapSaver
	{
	public:
		void saveBitmapToFile(pBitmap bitmap, const std::string& filename);
	};
}

#endif