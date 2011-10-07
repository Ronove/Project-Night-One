#ifndef HIGANBITMAPGENERATOR_H
#define HIGANBITMAPGENERATOR_H

#include <boost/shared_ptr.hpp>
#include "Bitmap.h"

namespace higan
{
	class BitmapGenerator
	{
	public:
		virtual void process()=0;
	};

	typedef boost::shared_ptr<BitmapGenerator> pBitmapGenerator;
}

#endif