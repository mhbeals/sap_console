#pragma once
#include "coresettings.h"
#include "inputter.h"

class processor : public inputter
{
public:

	// uniquePagesTable creator
	void processDirectLinkComparisons() //creates a list of ancestor-descendent (directed link) pairs
	{
		
		std::string UID; //unique article id
		int targetIndex;
		std::string BestMatch; //variable to indicate highest perfect match score
		int Score; //perfect match score
		bool bIsEarliest;
		for (int it = 0; it < size(uniquePagesTable); ++it) //for each unique article id
		{
			UID = uniquePagesTable[it].nameOfLaterPage; //set UID to unique article id
			targetIndex = 0; //set targetIndex to null
			BestMatch = ""; //set BestMatch to null
			Score = 0; //set Score to null
			bIsEarliest = false; //boolean to indicate if it is earliest match
			int year = 0; //set year to null
			int month = 0; //set month to null
			int day = 0; //set day to null
			for (int j = 0; j < size(comparisonsTable); ++j) //go through the comparisons list
			{
				if (comparisonsTable[j].laterPage.normalisedNameOfPage == UID) //if a target article in that line of the comparisons matches current unique article id
				{
					if (comparisonsTable[j].perfectMatchOfComparison > Score) //check to see if better perfect match has already been found; if not, proceed
					{
						if (comparisonsTable[j].earlierPage.yearOfPage == comparisonsTable[j].laterPage.yearOfPage
							&& comparisonsTable[j].earlierPage.monthOfPage == comparisonsTable[j].laterPage.monthOfPage
							&& comparisonsTable[j].earlierPage.dayOfPage == comparisonsTable[j].laterPage.dayOfPage)
						{
						}
						else if (comparisonsTable[j].earlierPage.yearOfPage > comparisonsTable[j].laterPage.yearOfPage
							||
							comparisonsTable[j].earlierPage.yearOfPage == comparisonsTable[j].laterPage.yearOfPage
							&& comparisonsTable[j].earlierPage.monthOfPage > comparisonsTable[j].laterPage.monthOfPage
							||
							comparisonsTable[j].earlierPage.yearOfPage == comparisonsTable[j].laterPage.yearOfPage
							&& comparisonsTable[j].earlierPage.monthOfPage == comparisonsTable[j].laterPage.monthOfPage
							&& comparisonsTable[j].earlierPage.dayOfPage > comparisonsTable[j].laterPage.dayOfPage) //if source article is later than the target article
						{
							BestMatch = comparisonsTable[j].earlierPage.normalisedNameOfPage; //unique id of source
							Score = comparisonsTable[j].perfectMatchOfComparison; //set score as current best score
							bIsEarliest = true; //label target as earliest
							year = comparisonsTable[j].earlierPage.yearOfPage;  //set source year as year
							month = comparisonsTable[j].earlierPage.monthOfPage; //set source month as month
							day = comparisonsTable[j].earlierPage.dayOfPage; //set source day as day
						}
						else if (!bIsEarliest) //if no match has been found yet, print
						{
							BestMatch = comparisonsTable[j].earlierPage.normalisedNameOfPage; //unique id of source
							Score = comparisonsTable[j].perfectMatchOfComparison; //set score as current best score
							bIsEarliest = false; //allows it to keep searching for better matches
							year = comparisonsTable[j].earlierPage.yearOfPage; // set source year as year
							month = comparisonsTable[j].earlierPage.monthOfPage; //set source month as month
							day = comparisonsTable[j].earlierPage.dayOfPage; //set source day as day
						}
					}
					if (comparisonsTable[j].perfectMatchOfComparison == Score) //check to see if perfect match is the same as current source; if so, proceed
					{
						if (bIsEarliest) //if bIsEarliest is set to true; shouldn't be
						{
							if (comparisonsTable[j].earlierPage.yearOfPage > year
								||
								comparisonsTable[j].earlierPage.yearOfPage == year
								&& comparisonsTable[j].earlierPage.monthOfPage > month
								||
								comparisonsTable[j].earlierPage.yearOfPage == year
								&& comparisonsTable[j].earlierPage.monthOfPage == month
								&& comparisonsTable[j].earlierPage.dayOfPage > day) //if current test is earlier than previous best match, replace entries with new data
							{
								BestMatch = comparisonsTable[j].earlierPage.normalisedNameOfPage; //set as best match for target
								Score = comparisonsTable[j].perfectMatchOfComparison; //set as new score
								bIsEarliest = true; //label target as earliest
								year = comparisonsTable[j].earlierPage.yearOfPage;  //set source year as year
								month = comparisonsTable[j].earlierPage.monthOfPage; //set source month as month
								day = comparisonsTable[j].earlierPage.dayOfPage; //set source day as day
							}
						}
						else if (comparisonsTable[j].earlierPage.yearOfPage > comparisonsTable[j].laterPage.yearOfPage
							||
							comparisonsTable[j].earlierPage.yearOfPage == comparisonsTable[j].laterPage.yearOfPage
							&& comparisonsTable[j].earlierPage.monthOfPage > comparisonsTable[j].laterPage.monthOfPage
							||
							comparisonsTable[j].earlierPage.yearOfPage == comparisonsTable[j].laterPage.yearOfPage
							&& comparisonsTable[j].earlierPage.monthOfPage == comparisonsTable[j].laterPage.monthOfPage
							&& comparisonsTable[j].earlierPage.dayOfPage > comparisonsTable[j].laterPage.dayOfPage)//if current test is earlier than previous best match, replace entries with new data
						{
							BestMatch = comparisonsTable[j].earlierPage.normalisedNameOfPage; //unique id of source
							Score = comparisonsTable[j].perfectMatchOfComparison; //set score as current best score
							bIsEarliest = false; //allows it to keep searching for better matches
							year = comparisonsTable[j].earlierPage.yearOfPage; // set source year as year
							month = comparisonsTable[j].earlierPage.monthOfPage; //set source month as month
							day = comparisonsTable[j].earlierPage.dayOfPage; //set source day as day
						}
					}
				}
			}
			if (BestMatch == "") //if there was no best match
			{
				bIsEarliest = true; //label target as earliest
			}
			if (bIsEarliest) //if target is labeled as earliest 
			{
				uniquePagesTable[it].bHasNoDescendents = true; //label as DeadEnd
				uniquePagesTable[it].nameOfEarlierPage = BestMatch;
				uniquePagesTable[it].bHasDescendents = bIsEarliest;
			}
			else //if target is not labeled as earliest
			{
				uniquePagesTable[it].nameOfEarlierPage = BestMatch;
				uniquePagesTable[it].bHasDescendents = bIsEarliest;
			}
		}

	}
	void assignMaximumAverageWordCountValues() // creates a table of maximum wordcount values for each page and issue
	{
		int startValue = 0;
		for (int i = 0; i < copyfindTable.size(); i++)
		{
			int testmaxval = copyfindTable[i].copyfindAverageMatch; // set test wordcount to i
			int j = startValue;
			for (;j < copyfindTable.size(); j++)
			{
				// go through cf table
				if (copyfindTable[i].normalisedNameOfLeftPage == copyfindTable[j].normalisedNameOfLeftPage)
				{
					// test cfam value against every other cfam value for same page
					if (testmaxval < copyfindTable[j].copyfindAverageMatch)
					{
						// if new value is bigger than test value, change test value to new value
						testmaxval = copyfindTable[j].copyfindAverageMatch;
						startValue = j;
					}
				}
			}
			// once you've gone through all testable values, set cfmax value for current test value
			copyfindTable[i].copyfindMaximumWordCount = testmaxval;
		}

		for (int k = 0; k < uniquePagesTable.size(); k++)
		{
			// go through unique articles
			for (int l = 0; l < copyfindTable.size(); l++)
			{
				// go through copyfind table
				if (uniquePagesTable[k].nameOfLaterPage == copyfindTable[l].normalisedNameOfLeftPage)
				{
					uniquePagesTable[k].maximumAverageWordCountForReprintsOnLaterPage = copyfindTable[l].copyfindMaximumWordCount;
					uniquePagesTable[k].nameOfIssue = copyfindTable[l].issueNameofLeftPage;
					uniquePagesTable[k].fullWordCountOfIssue = copyfindTable[l].copyfindFullWordCountOfLeftIssue;
					uniquePagesTable[k].fullWordCountofLaterPage = copyfindTable[l].fullPageWordCountOfLeftPage;
					uniquePagesTable[k].percentageOfReprintedMaterialOnPage = uniquePagesTable[k].maximumAverageWordCountForReprintsOnLaterPage / uniquePagesTable[k].fullWordCountofLaterPage;
				}
			}
		}

		double testissuesum = 0;

		for (int k = 0; k < uniquePagesTable.size(); k++)
		{
			testissuesum = uniquePagesTable[k].maximumAverageWordCountForReprintsOnLaterPage;
			// go through unique articles
			for (int l = 0; l < uniquePagesTable.size(); l++)
			{
				// go through copyfind table
				if (uniquePagesTable[k].nameOfIssue == uniquePagesTable[l].nameOfIssue
					&&
					uniquePagesTable[k].nameOfLaterPage != uniquePagesTable[l].nameOfLaterPage)
				{
					testissuesum += uniquePagesTable[l].maximumAverageWordCountForReprintsOnLaterPage;
				}
			}
			uniquePagesTable[k].combinedAverageWordCountForIssue = testissuesum;
			uniquePagesTable[k].percentageOfReprintedMaterialInIssue = uniquePagesTable[k].combinedAverageWordCountForIssue / uniquePagesTable[k].fullWordCountOfIssue;
		}
	}

// general processes
void clearVectors() {
	wordCountTable.clear();
	copyfindTable.clear();
	normalisedTitlesTable.clear();
	comparisonsTable.clear();
	uniquePagesTable.clear();
}
};