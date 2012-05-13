#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <sstream>

#include <boost/bind.hpp>

#include "CSVReader.h"

struct GlossaryEntry
{
	GlossaryEntry(const std::string& button, const std::string& text);
	std::string buttonImage;
	std::string textImage;
};

struct GlossaryData
{
	static const unsigned entriesPerPage = 8;
	unsigned numPages;
	std::vector<GlossaryEntry> glossaryEntries;
};

void processInputLine(std::vector<std::string>& csvLine, GlossaryData& data);
std::stringstream createGlossaryPageMode(const GlossaryData& data);
std::stringstream createGlossaryButtonMode(const GlossaryData& data);

int main(int argc, char* argv[])
{
	if(argc != 3)
	{
		std::cerr << "Error: use is " << argv[0] << " <input file> <output file>" << std::endl;
		return 1;
	}

	higan::CSVReader inputFile;
	GlossaryData glossaryData;

	// Open the input file to read options
	inputFile.openFile(argv[1]);
	while(inputFile.hasMoreRows())
	{
		std::vector<std::string> row = inputFile.getRow();
		row.pop_back();
		processInputLine(row,glossaryData);
	}
	inputFile.closeFile();

	std::ofstream outputFile(argv[2]);

	// Open segments which are plain text that don't need modifications
	std::vector<std::ifstream> parts(4);
	for(unsigned i = 0; i < parts.size(); ++i)
	{
		std::stringstream ss;
		ss << "part" << i+1 << ".txt";
		parts[i].open(ss.str());
		if(parts[i].bad())
		{
			std::cerr << "Error: could not open " << ss.str() << std::endl;
			return 2;
		}
	}

	outputFile << parts[0].rdbuf();
	outputFile << glossaryData.numPages;
	outputFile << parts[1].rdbuf();
	outputFile << createGlossaryPageMode(glossaryData).rdbuf();
	outputFile << parts[2].rdbuf();
	outputFile << createGlossaryButtonMode(glossaryData).rdbuf();
	outputFile << parts[3].rdbuf();
	outputFile.close();

	std::cout << "Successfully created " << argv[2] << " from " << argv[1] << std::endl;
}

GlossaryEntry::GlossaryEntry(const std::string& button, const std::string& text):
buttonImage(button),
textImage(text)
{	}

void processInputLine(std::vector<std::string>& csvLine, GlossaryData& data)
{
	if(csvLine.size() != 2)
	{
		std::cerr << "Error in line: ";
		std::for_each(csvLine.begin(), csvLine.end(), [](std::string& entry){ std::cerr << "{" << entry << "}"; });
		std::cerr << std::endl;
		std::cerr << "Expects 2 items per line, but got " << csvLine.size() << "." << std::endl;
		return;
	}

	data.glossaryEntries.push_back(GlossaryEntry(csvLine[0], csvLine[1]));
	data.numPages = int(ceil((float)data.glossaryEntries.size() / GlossaryData::entriesPerPage));
}

std::stringstream createGlossaryPageMode(const GlossaryData& data)
{
	std::stringstream output;

	for(unsigned i = 0; i < data.numPages; ++i)
	{
		output << "notif %EN_glossary_page_view = ";
		output << i+1;
		output << " jumpf";
		output << std::endl;

		int entriesLeftUnprocessed = data.glossaryEntries.size() - i * data.entriesPerPage;
		unsigned entriesOnThisPage = entriesLeftUnprocessed < data.entriesPerPage ?
entriesLeftUnprocessed : data.entriesPerPage;
			
		for(unsigned j = 0; j < data.entriesPerPage; ++j)
		{
			output << "\tnotif %EN_glossary_progress > " << i*data.entriesPerPage + j << " jumpf" << std::endl;
			// add entry to hints
				output << "\t\tlsp EN_hint_button_";
				output << j;
				output << ",\":a/2,0,3;";
				std::string buttonImage = j < entriesOnThisPage? data.glossaryEntries[i*data.entriesPerPage + j].buttonImage : "";
				output << buttonImage;
				output << "\", %Free4, %Free5 : add %Free5, %Free6";
				output << std::endl;
			output << "\t~" << std::endl;
		}
		output << "~";
		output << std::endl;
	}

	output << std::endl;
	output << "return";
	output << std::endl;
	output << std::endl;
	
	return output;
}

std::stringstream createGlossaryButtonMode(const GlossaryData& data)
{
	std::stringstream output;

	for(unsigned i = 0; i < data.numPages; ++i)
	{
		int entriesLeftUnprocessed = data.glossaryEntries.size() - i * data.entriesPerPage;
		unsigned entriesOnThisPage = entriesLeftUnprocessed < data.entriesPerPage ?
entriesLeftUnprocessed : data.entriesPerPage;

		for(unsigned j = 0; j < entriesOnThisPage; ++j)
		{
			output << "notif %EN_glossary_page view = ";
			output << i+1;
			output << " && %EN_glossary_current_hint = ";
			output << j;
			output << " jumpf";
			output << std::endl;

			output << "\tlsp rmenu_back, \":a;";
			output << data.glossaryEntries[i*data.entriesPerPage+j].textImage;
			output << "\",%Free2,%Free3";
			output << std::endl;

			output << "~";
			output << std::endl;
		}
	}

	output << std::endl;
	output << "return";
	output << std::endl;
	output << std::endl;

	return output;
}
