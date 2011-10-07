#include "MainApp.h"

#include "BitmapGenerator.h"
#include "HintGenerator.h"

namespace higan
{
	MainApp::MainApp(int argc, char* argv[])
	{
		if(argc != 2)
		{
			std::string error = "Wrong number of arguments";
			assert(false);
		}

		bitmapGenerator.reset(new HintGenerator(argv[1]));
	}

	MainApp::~MainApp()
	{
	}

	void MainApp::exec()
	{
		bitmapGenerator->process();
	}
}