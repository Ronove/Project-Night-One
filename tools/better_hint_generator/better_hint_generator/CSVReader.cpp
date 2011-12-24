#include "csv_parser/csv_parser.hpp"
#include <cassert>
#include "CSVReader.hpp"

CSVReader::CSVReader()
	: parser_(0)
{
}

CSVReader::~CSVReader()
{
	delete parser_;
}

void CSVReader::openFile(const std::string& filename)
{
	parser_ = new csv_parser();

	bool success = parser_->init(filename.c_str());

	if(!success)
	{
		std::string error = "Failed to open file: " + filename;
		assert(false);
		closeFile();
	}
	else
	{
		parser_->set_field_term_char(',');
		parser_->set_line_term_char('\n');
		parser_->set_enclosed_char('\"',ENCLOSURE_OPTIONAL);
	}
}

void CSVReader::closeFile()
{
	delete parser_;
	parser_ = 0;
}

bool CSVReader::isOpened() const
{
	return parser_ != 0;
}

std::vector<std::string> CSVReader::getRow()
{
	if(!parser_)
	{
		std::string error = "Tried to get row from an unopened csv file.";
		assert(false);
		return std::vector<std::string>();
	}
	else if(!hasMoreRows())
	{
		std::string error = "Tried to get a row from outside a csv file's bounds.";
		assert(false);
		return std::vector<std::string>();
	}

	return parser_->get_row();
}

bool CSVReader::hasMoreRows() const
{
	if(!parser_)
	{
		std::string error = "Tried to check if an unopened csv file had more rows";
		assert(false);
		return false;
	}

	return parser_->has_more_rows();
}
