#ifndef CSVREADER_H
#define CSVREADER_H

#include <vector>
#include <string>

class csv_parser;

class CSVReader
{
public:
	CSVReader();
	~CSVReader();

	void openFile(const std::string& filename);
	void closeFile();
	bool isOpened() const;

	std::vector<std::string> getRow();
	bool hasMoreRows() const;
private:
	csv_parser* parser_;
};

#endif
