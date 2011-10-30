#ifndef HIGAN_CSVREADER_H
#define HIGAN_CSVREADER_H

#include <vector>
#include <string>
#include <boost/scoped_ptr.hpp>
#include "csv_parser.hpp"

namespace higan
{
	class CSVReader
	{
		boost::scoped_ptr<csv_parser> pParser;
	public:
		void openFile(const std::string& filename);
		void closeFile();

		std::vector<std::string> getRow();
		bool hasMoreRows() const;
	};
}

#endif