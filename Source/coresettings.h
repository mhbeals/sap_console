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
#include "dateUtilities.h"

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

void requestDataPacket(int coreID);
