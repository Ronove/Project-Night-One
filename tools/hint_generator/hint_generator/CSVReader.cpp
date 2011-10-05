#include "csv_parser/csv_parser.hpp"

#include "CSVReader.h"

namespace higan
{
	void CSVReader::openFile(const std::string& filename)
	{
		pParser.reset(new csv_parser());

		bool success = pParser->init(filename.c_str());

		if(!success)
		{
			throw "Failed to open file: " + filename;
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
			throw "Tried to get row from an unopened csv file.";
		}
		else if(!hasMoreRows())
		{
			throw "Tried to get a row from outside a csv file's bounds.";
		}
		else
		{
			return pParser->get_row();
		}
	}

	bool CSVReader::hasMoreRows() const
	{
		if(!pParser)
		{
			throw "Tried to check if an unopened csv file had more rows";
		}

		return pParser->has_more_rows();
	}
	
}