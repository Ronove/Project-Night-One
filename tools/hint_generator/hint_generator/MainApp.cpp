#include "MainApp.h"

#include "BitmapGenerator.h"
#include "HintGenerator.h"

namespace higan
{
	MainApp::MainApp(int argc, char* argv[])
	{
		bitmapGenerator.reset(new HintGenerator());
	}

	MainApp::~MainApp()
	{
	}

	void MainApp::exec()
	{
		bitmapGenerator->process();
	}
}