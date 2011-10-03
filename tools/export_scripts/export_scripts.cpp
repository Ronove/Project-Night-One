#include <iostream>
#include <fstream>
#include <string>

// Appends another file to the build
void addEntry(std::ofstream& outputFile, const std::string& outputfilename, const std::string& inputfilename)
{
	outputFile << "copy /a " << outputfilename << "+" << inputfilename << " " << outputfilename << std::endl;
}

int main(int argc, char* argv[])
{
	if(argc != 3)
	{
		if(argc < 3)
		{
			std::cerr << "Not enough arguments." << std::endl;
		}
		else
		{
			std::cerr << "Too many arguments." << std::endl;
		}
		
		std::cerr << "Format is: " << std::endl;
		std::cerr << "update_compile <input> <output>" << std::endl;
		
		return -1;
	}
	
	std::string outputFileName = argv[2];
	
	// Input is the given file
	std::ifstream inputFile(argv[1]);
	std::cout << "Reading input from file: " << argv[1] << std::endl;
	if(inputFile.bad())
	{
		std::cerr << argv[1] << " is not good for read operations." << std::endl;
		return -1;
	}
	
	std::ofstream outputFile(outputFileName.c_str());
	std::cout << "Output to " << outputFileName << std::endl;
	if(outputFile.bad())
	{
		std::cerr << outputFileName << " is not good for write operations." << std::endl;
	}
	
	// Begin writing the file
	
	// line which will delete the old 0.txt
	outputFile << "del 0.txt" << std::endl;
	outputFile << "copy /y nul 0.txt" << std::endl;
	
	while(!inputFile.eof())
	{
		std::string currentLine;

		std::getline(inputFile,currentLine);
		addEntry(outputFile,"0.txt",currentLine);
		
		std::cout << "Added " << currentLine << " to " << outputFileName << std::endl;
	}
	
	std::cout << "Done." << std::endl;
	return 0;
}