#include <fstream>
#include <sstream>
#include <string>

#include "TextReader.h"

namespace higan
{
	std::string TextReader::fileToString(const std::string& filename)
	{
		std::ifstream inputStream(filename);
		if(inputStream.bad())
		{
			throw "File: " + filename + " is bad for IO operations.";
		}

		std::stringstream outputStream;
		outputStream << inputStream;
		
		return outputStream.str();
	}
}