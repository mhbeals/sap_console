#pragma once
#include "coresettings.h"
#include "writer.h"
class runner;
int activeThread = 0;
extern variableList processVariables;

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

		makeNormalisedTitleTable();

		// Inputs
		std::string inputs = inputFileStructureLocation + "\\inputs\\";
		// Outputs
		std::string outputs = inputFileStructureLocation + "\\outputs\\";
		// Previous file
		std::string previous = processVariables.stringOfPreviousYear + "_" + processVariables.stringOfPreviousMonth + ".tsv";
		// Current file
		std::string focus = processVariables.stringOfYear + "_" + processVariables.stringOfMonth + ".tsv";
		// Subsequent file
		std::string subsequent = processVariables.stringOfSubsequentYear + "_" + processVariables.stringOfSubsequentMonth + ".tsv";

		importWordCountData();
		importCopyfindData();
		regexUniquePageEntriesTitles();
		calculateMaximumIssueWordCount();
		writeOutputs();
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
