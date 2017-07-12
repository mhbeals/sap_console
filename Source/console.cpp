// Scissors and Paste Console
// M. H. Beals (2017) v.0.3.6 [Software]

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
int inputEndYear = 1900;
int assumedStartMonth = 1;
std::string promptContainer = "";
int eRequest = -1;
variableList inputVariables;

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

variableList varList(int yearBeingProcessed, int monthBeingProcessed)
{
	if (monthBeingProcessed == 1)
	{
		inputVariables.stringOfPreviousYear = std::to_string(yearBeingProcessed - 1);
		inputVariables.stringOfYear = std::to_string(yearBeingProcessed);
		inputVariables.stringOfSubsequentYear = std::to_string(yearBeingProcessed);
		inputVariables.stringOfPreviousMonth = "12";
		inputVariables.stringOfMonth = "01";
		inputVariables.stringOfSubsequentMonth = "02";
		return inputVariables;
	}
	else if (monthBeingProcessed < 9)
	{
		inputVariables.stringOfPreviousYear = std::to_string(yearBeingProcessed);
		inputVariables.stringOfYear = std::to_string(yearBeingProcessed);
		inputVariables.stringOfSubsequentYear = std::to_string(yearBeingProcessed);
		inputVariables.stringOfPreviousMonth = "0" + std::to_string(monthBeingProcessed - 1);
		inputVariables.stringOfMonth = "0" + std::to_string(monthBeingProcessed);
		inputVariables.stringOfSubsequentMonth = "0" + std::to_string(monthBeingProcessed +1);
		return inputVariables;
	}
	else if (monthBeingProcessed == 9)
	{
		inputVariables.stringOfPreviousYear = std::to_string(yearBeingProcessed);
		inputVariables.stringOfYear = std::to_string(yearBeingProcessed);
		inputVariables.stringOfSubsequentYear = std::to_string(yearBeingProcessed);
		inputVariables.stringOfPreviousMonth = "08";
		inputVariables.stringOfMonth = "09";
		inputVariables.stringOfSubsequentMonth = "10";
		return inputVariables;
	}
	else if (monthBeingProcessed == 10)
	{
		inputVariables.stringOfPreviousYear = std::to_string(yearBeingProcessed);
		inputVariables.stringOfYear = std::to_string(yearBeingProcessed);
		inputVariables.stringOfSubsequentYear = std::to_string(yearBeingProcessed);
		inputVariables.stringOfPreviousMonth = "09";
		inputVariables.stringOfMonth = "10";
		inputVariables.stringOfSubsequentMonth = "11";
		return inputVariables;
	}
	else if (monthBeingProcessed == 11)
	{
		inputVariables.stringOfPreviousYear = std::to_string(yearBeingProcessed);
		inputVariables.stringOfYear = std::to_string(yearBeingProcessed);
		inputVariables.stringOfSubsequentYear = std::to_string(yearBeingProcessed);
		inputVariables.stringOfPreviousMonth = "10";
		inputVariables.stringOfMonth = "11";
		inputVariables.stringOfSubsequentMonth = "12";
		return inputVariables;
	}
	else
	{
		inputVariables.stringOfPreviousYear = std::to_string(yearBeingProcessed);
		inputVariables.stringOfYear = std::to_string(yearBeingProcessed);
		inputVariables.stringOfSubsequentYear = std::to_string(yearBeingProcessed+1);
		inputVariables.stringOfPreviousMonth = "11";
		inputVariables.stringOfMonth = "12";
		inputVariables.stringOfSubsequentMonth = "01";
		return inputVariables;
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
			assumedStartMonth = j;
			inputVariables = varList(i, j);

			// Process Data
			
			while (eRequest == -1)
			{
				_sleep(1); // Required for Release
			}
			Thread[eRequest]->processVariables.stringOfYear = inputVariables.stringOfYear;
			Thread[eRequest]->processVariables.stringOfMonth = inputVariables.stringOfMonth;
			Thread[eRequest]->processVariables.stringOfPreviousYear = inputVariables.stringOfPreviousYear;
			Thread[eRequest]->processVariables.stringOfPreviousMonth = inputVariables.stringOfPreviousMonth;
			Thread[eRequest]->processVariables.stringOfSubsequentYear = inputVariables.stringOfSubsequentYear;
			Thread[eRequest]->processVariables.stringOfSubsequentMonth = inputVariables.stringOfSubsequentMonth;
			std::cout << "\nInputting " << getMonth(j) << " " << i;
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