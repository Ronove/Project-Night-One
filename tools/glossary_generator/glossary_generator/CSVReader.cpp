#include "csv_parser.hpp"

#include <cassert>

#include "CSVReader.h"

namespace higan
{
	void CSVReader::openFile(const std::string& filename)
	{
		pParser.reset(new csv_parser());

		bool success = pParser->init(filename.c_str());

		if(!success)
		{
			std::string error = "Failed to open file: " + filename;
			assert(false);
		}

		pParser->set_field_term_char(',');
		pParser->set_line_term_char('\n');
		pParser->set_enclosed_char('\"',ENCLOSURE_OPTIONAL);
	}

	void CSVReader::closeFile()
	{
		pParser.reset(0);
	}

	std::vector<std::string> CSVReader::getRow()
	{
		if(!pParser)
		{
			std::string error = "Tried to get row from an unopened csv file.";
			assert(false);
		}
		else if(!hasMoreRows())
		{
			std::string error = "Tried to get a row from outside a csv file's bounds.";
			assert(false);
		}

		return pParser->get_row();
	}

	bool CSVReader::hasMoreRows() const
	{
		if(!pParser)
		{
			std::string error = "Tried to check if an unopened csv file had more rows";
			assert(false);
		}

		return pParser->has_more_rows();
	}
	
}