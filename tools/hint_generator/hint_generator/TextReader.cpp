#include <fstream>
#include <sstream>
#include <string>
#include <cassert>

#include "TextReader.h"

namespace higan
{
	std::string TextReader::fileToString(const std::string& filename)
	{
		std::ifstream inputStream(filename);
		if(inputStream.bad())
		{
			std::string error = "File: " + filename + " is bad for IO operations.";
			assert(false);
		}

		std::stringstream outputStream;
		outputStream << inputStream;
		
		return outputStream.str();
	}
}