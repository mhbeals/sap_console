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
		importWordCountData();
		importCopyfindData();
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
