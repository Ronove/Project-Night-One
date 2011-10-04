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
		void SaveBitmapToFile(pBitmap bitmap, const std::string& filename);
		void SaveLog(const std::string& filename);
	protected:
		std::list<std::pair<std::string,bool> > m_log;
	};
}

#endif