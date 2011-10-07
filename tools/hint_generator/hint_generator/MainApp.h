#ifndef HIGANMAINAPP_H
#define HIGANMAINAPP_H

#include "BitmapGenerator.h"

namespace higan
{
	class MainApp
	{
		pBitmapGenerator bitmapGenerator;

	public:
		MainApp(int argc, char* argv[]);
		~MainApp();

		void exec();
	};
}

#endif