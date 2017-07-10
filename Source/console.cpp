// Scissors and Paste Console
// M. H. Beals (2017) v.0.3.3 [Software]

// MIT License
// Copyright(c) 2017 M. H. Beals
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files(the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// // to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions :
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include "stdafx.h"
#include "coresettings.h"
#include "runner.h"

// Starting Variables
std::string inputFileStructureLocation = "g:\\sap_reprints";
int inputStartYear = 1800;
int inputEndYear = 1801;
int assumedStartMonth = 1;
std::string promptContainer = "";
int eRequest = -1;

unsigned int NumberOfThreads;
std::vector<std::thread> t;
bool bCatchOverflow = false;

// Console functions


void recordRunner(runner* thisRunner)
{
	Thread.push_back(thisRunner);
}

void incrementActiveThread()
{
	if (activeThread == NumberOfThreads-1)
	{
		activeThread = 0;
	}
	else
	{
		activeThread++;
	}
}

void requestDataPacket(int coreID)
{
	eRequest = coreID;
	
	while (eRequest > -1)
	{
		_sleep(1); // Required for Release
		if (bCatchOverflow)
		{
			Thread[coreID]->bRunComplete = true;
			eRequest = -1;
			return;
		}
	}
	incrementActiveThread();
}

void stopThreads()
{
	for (unsigned i = 0; i < NumberOfThreads; i++)
	{
		Thread[i]->bRunComplete = true;
	}
	bCatchOverflow = true;
}

void waitForThreads()
{
	unsigned reg = 0;
	while (reg != NumberOfThreads)
	{
		reg = 0;
		for (unsigned i = 0; i < NumberOfThreads; i++)
		{
			if (Thread[i]->bAnalysisComplete)
			{
				reg++;
			}
			else
			{
			}
		}
	}
}

std::string varList(int yearBeingProcessed, int monthBeingProcessed)
{
	if (monthBeingProcessed == 1)
	{
		std::ostringstream listOfMonthsAndYears;
		listOfMonthsAndYears << yearBeingProcessed << ",0" << monthBeingProcessed << "," << yearBeingProcessed << ",0" << monthBeingProcessed + 1 << "," << yearBeingProcessed - 1 << ",12";
		return listOfMonthsAndYears.str();
	}
	else if (monthBeingProcessed < 9)
	{
		std::ostringstream listOfMonthsAndYears;
		listOfMonthsAndYears << yearBeingProcessed << ",0" << monthBeingProcessed << "," << yearBeingProcessed << ",0" << monthBeingProcessed + 1 << "," << yearBeingProcessed << ",0" << monthBeingProcessed - 1;
		return listOfMonthsAndYears.str();
	}
	else if (monthBeingProcessed == 9)
	{
		std::ostringstream listOfMonthsAndYears;
		listOfMonthsAndYears << yearBeingProcessed << ",0" << monthBeingProcessed << "," << yearBeingProcessed << "," << monthBeingProcessed + 1 << "," << yearBeingProcessed << ",08";
		return listOfMonthsAndYears.str();
	}
	else if (monthBeingProcessed == 10)
	{
		std::ostringstream listOfMonthsAndYears;
		listOfMonthsAndYears << yearBeingProcessed << "," << monthBeingProcessed << "," << yearBeingProcessed << "," << monthBeingProcessed + 1 << "," << yearBeingProcessed << "," << ",09";
		return listOfMonthsAndYears.str();
	}
	else if (monthBeingProcessed == 11)
	{
		std::ostringstream listOfMonthsAndYears;
		listOfMonthsAndYears << yearBeingProcessed << "," << monthBeingProcessed << "," << yearBeingProcessed << "," << monthBeingProcessed + 1 << "," << yearBeingProcessed << "," << monthBeingProcessed - 1;
		return listOfMonthsAndYears.str();
	}
	else
	{
		std::ostringstream listOfMonthsAndYears;
		listOfMonthsAndYears << yearBeingProcessed << "," << monthBeingProcessed << "," << yearBeingProcessed + 1 << ",01" << "," << yearBeingProcessed << ",11";
		return listOfMonthsAndYears.str();
	}
}


int main()
{
	//Create runners
	unsigned int FreeThreads = 1;
	NumberOfThreads = std::thread::hardware_concurrency();

	// Prompts
	std::cout << "Welcome to the Scissors and Paste Console." << std::endl << std::endl;
	if (NumberOfThreads > 1)
	{
		std::cout << "There are an estimated " << NumberOfThreads << " threads available for this task." << std::endl;
		std::cout << "How many threads do you want to leave for other processes?" << std::endl;
		std::cin >> FreeThreads;
		std::cout << std::endl << std::endl;
	}

	unsigned int scratch = NumberOfThreads - FreeThreads-1;
	NumberOfThreads = scratch;

	// Prompts
	std::cout << "Your pre-set variables are:" << std::endl;
	std::cout << "Starting Year: " << inputStartYear << std::endl;
	std::cout << "Ending Year: " << inputEndYear << std::endl;
	std::cout << "File Structure Location: " << inputFileStructureLocation << std::endl;
	std::cout << "Would you like to change the dates?" << std::endl;
	std::cin >> promptContainer;
	if (promptContainer == "y")
	{
		std::cout << "Starting Year? ";
		std::cin >> inputStartYear;
		std::cout << std::endl << "Ending Year? ";
		std::cin >> inputEndYear;
	}
	else
	{
		std::cout << "Keeping standard dates..." << std::endl;
	}
	std::cout << "Would you like to change the file structure location? Remember to use double backslashes" << std::endl;
	std::cin >> promptContainer;
	if (promptContainer == "y")
	{
		std::cout << "Structure location. Remember to use a double backslash rather than a single one";
		std::cin >> inputFileStructureLocation;
		std::cout << std::endl;
	}
	else
	{
		std::cout << "Keeping standard location..." << std::endl;
	}
	
	// Initialise Runner IDs
	
	for (unsigned i = 0; i < NumberOfThreads; ++i)
	{
				std::thread th(&runner::runAnalysis, new runner);
		t.push_back(std::move(th));
		t[i].detach();
		while (Thread.size() <= i) {}
		Thread[i]->coreID = i;
	}

	for (int i = inputStartYear; i <= inputEndYear; i++)
	{
		inputStartYear = i;

		for (int j = assumedStartMonth; j < 13; j++)
		{
			std::cout << "\nProcessing " << getMonth(j) << " " << i;
			assumedStartMonth = j;
			std::string listOfMonthsAndYears = varList(i, j);
			std::string stringOfPreviousYear = listOfMonthsAndYears.substr(16, 4);
			std::string stringOfYear = listOfMonthsAndYears.substr(0, 4);
			std::string stringOfSubsequentYear = listOfMonthsAndYears.substr(8, 4);
			std::string stringOfPreviousMonth = listOfMonthsAndYears.substr(21, 2);
			std::string stringOfMonth = listOfMonthsAndYears.substr(5, 2);
			std::string stringOfSubsequentMonth = listOfMonthsAndYears.substr(13, 2);

			// Process Data
			
			while (eRequest == -1)
			{
				_sleep(1); // Required for Release
			}
			
			Thread[eRequest]->inputFileStructureLocation = inputFileStructureLocation;
			Thread[eRequest]->stringOfYear =stringOfYear;
			Thread[eRequest]->stringOfMonth = stringOfMonth;
			Thread[eRequest]->stringOfPreviousYear = stringOfPreviousYear;
			Thread[eRequest]->stringOfPreviousMonth = stringOfPreviousMonth;
			Thread[eRequest]->stringOfSubsequentYear = stringOfSubsequentYear;
			Thread[eRequest]->stringOfSubsequentMonth = stringOfSubsequentMonth;
			
			eRequest = -1;
		}
		assumedStartMonth = 1;
	}
	stopThreads();
	waitForThreads();
	int pause = 0;

	std::cout << std::endl << std::endl << "Enter any key to exit..." << std::endl; // Hold for exit
	std::cin >> pause;
	return 0;
}