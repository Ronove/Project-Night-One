#ifndef HIGAN_TEXTREADER_H
#define HIGAN_TEXTREADER_H

#include <string>

namespace higan
{
	class TextReader
	{
	public:
		std::string fileToString(const std::string& filename);
	};
}

#endif