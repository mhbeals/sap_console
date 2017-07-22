#pragma once
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>
#include <ostream>
#include <istream>
#include <algorithm>
#include <thread>

extern std::string inputFileStructureLocation;

struct variableList
{
	std::string stringOfYear;
	std::string stringOfMonth;
	std::string stringOfPreviousYear;
	std::string stringOfPreviousMonth;
	std::string stringOfSubsequentYear;
	std::string stringOfSubsequentMonth;
};

// Match Struct (For Copyfind Match Entries; each entry has different data but may share pages)
struct matchDataEntry // Contains Copyfind Match Data
{
	int copyfindPerfectMatch; // Pulled directly from Copyfind Manifest
	size_t earlierPageEntryIndexNumber; // Inputted based on enumerateDate() results
	double copyfindEarlierMatchWordCount;   // Inputted based on enumerateDate() results
	size_t laterPageEntryIndexNumber;  // Inputted based on enumerateDate() results
	double copyfindLaterPageMatchWordCount;  // Inputted based on enumerateDate() results
	double copyfindAverageMatch; // Computed average of copyfindLeftMatch and copyfindRightMatch after enumerateDate() results
	int daysBetween; // Days between match pages
	int earlierEnumeratedDate; // Use for sorting outputs
	std::string earlierTitle; // Used for sorting outputs
	std::string earlierPageNumber;  // Used for sorting outputs
	bool bMeme{ false }; // Does match meet basic wordcount, date and self-match requirements
};

void requestDataPacket(int coreID);
std::string getMonth(int month);
