#pragma once
#include "coresettings.h"
#include "writer.h"
class runner;
int activeThread = 0;

std::vector<runner*> Thread;

class runner : public writer
{
public:
	
	// Variables
	int coreID = -1;
	bool bRunComplete = false;
	bool bAnalysisComplete = false;

	//Constructor
	runner::runner(void) 
	{ 
		Thread.push_back(this);
	}

	void runAnalysis()
	{
	dataReceived:
		while (activeThread!=coreID && !bRunComplete)
		{
			_sleep(1); // Required for Release
		}
		if (!bRunComplete)
		{
			requestDataPacket(coreID);
		}

		makeCopyFindTable();
		makeNormalisedTitleTable(inputFileStructureLocation);
		makeWordCountTable(inputFileStructureLocation, stringOfYear, stringOfMonth, stringOfSubsequentYear, stringOfSubsequentMonth, stringOfPreviousYear, stringOfPreviousMonth);
		
		std::cout << "\n\tProcessing Comparisons for " << stringOfMonth << " " << stringOfYear;
		regexCopyfindTableTitles();
		makeComparisonsTable();
		crossReferenceValuesInWordCountAndCopyfindTables();

		std::cout << "\n\t\tProcessing Unique Pages for " << stringOfMonth << " " << stringOfYear;
		processDirectLinkComparisons();
		assignMaximumAverageWordCountValues();
		
		std::cout << "\n\t\t\tWriting Files for " << stringOfMonth << " " << stringOfYear;
		writeAllFiles(inputFileStructureLocation, stringOfYear, stringOfMonth);
		
		clearVectors();
		if (!bRunComplete)
		{
			goto dataReceived;
		}
		else
		{
			bAnalysisComplete = true;
			while (bRunComplete)
			{
			}
		}
	}
};
