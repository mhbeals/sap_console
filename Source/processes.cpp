#pragma once
#include "stdafx.h"
#include "processes.h"
#include "dateutil.h"
#include "coresettings.h"
#include "inputter.h"

vector<copyfindEntry> copyfindTable; //vector for raw Copyfind data
vector<wordCountTableEntry> wordCountTable; //vector for British Library wordcount data
vector<normalisedTitleReference> normalisedTitlesTable; //vector for normalised titles

void regexCopyfindTableTitles()
{
	for (int i = 0; i < copyfindTable.size(); i++)
	{
		regex t("([A-Za-z-,'&]+)_[A-Z_0-9]+.txt");
		regex p("[A-Za-z-,'&]+_([A-Z_0-9]+).txt");
		regex u("([0-9]{4}.[0-9]{2}.[0-9]{2}_[A-Za-z-,'&]+_[A-Z_0-9]+).txt");
		string normallefttitle = "";
		string templefttitle = "";
		string normalrighttitle = "";
		string temprighttitle = "";

		copyfindTable[i].yearOfLeftPage = stoi(copyfindTable[i].copyfindPathOfLeftFile.substr(23, 4));
		copyfindTable[i].monthOfLeftPage = stoi(copyfindTable[i].copyfindPathOfLeftFile.substr(28, 2));
		copyfindTable[i].dayOfLeftPage = stoi(copyfindTable[i].copyfindPathOfLeftFile.substr(31, 2));
		templefttitle = regex_replace(copyfindTable[i].copyfindPathOfLeftFile.substr(34), t, "$1");
		for (int j = 0; j < size(normalisedTitlesTable); j++)
		{
			if (templefttitle == normalisedTitlesTable[j].title)
			{
				normallefttitle = normalisedTitlesTable[j].normalisedTitle;
			}
		}
		copyfindTable[i].titleOfLeftPage = normallefttitle;
		copyfindTable[i].pageNumberOfLeftPage = regex_replace(copyfindTable[i].copyfindPathOfLeftFile.substr(34), p, "$1");
		copyfindTable[i].normalisedNameOfLeftPage = copyfindTable[i].copyfindPathOfLeftFile.substr(23, 4) + "." + copyfindTable[i].copyfindPathOfLeftFile.substr(28, 2) + "." + copyfindTable[i].copyfindPathOfLeftFile.substr(31, 2) + "_" + normallefttitle + "_" + regex_replace(copyfindTable[i].copyfindPathOfLeftFile.substr(34), p, "$1");
		copyfindTable[i].nameOfLeftPage = regex_replace(copyfindTable[i].copyfindPathOfLeftFile.substr(23), u, "$1");
		copyfindTable[i].yearOfRightPage = stoi(copyfindTable[i].copyfindPathOfRightFile.substr(23, 4));
		copyfindTable[i].monthOfRightPage = stoi(copyfindTable[i].copyfindPathOfRightFile.substr(28, 2));
		copyfindTable[i].dayOfRightPage = stoi(copyfindTable[i].copyfindPathOfRightFile.substr(31, 2));
		temprighttitle = regex_replace(copyfindTable[i].copyfindPathOfRightFile.substr(34), t, "$1");
		for (int j = 0; j < size(normalisedTitlesTable); j++)
		{
			if (temprighttitle == normalisedTitlesTable[j].title)
			{
				normalrighttitle = normalisedTitlesTable[j].normalisedTitle;
			}
		}
		copyfindTable[i].titleOfRightPage = normalrighttitle;
		copyfindTable[i].pageOfRightPage = regex_replace(copyfindTable[i].copyfindPathOfRightFile.substr(34), p, "$1");
		copyfindTable[i].normalisedNameOfRightPage = copyfindTable[i].copyfindPathOfRightFile.substr(23, 4) + "." + copyfindTable[i].copyfindPathOfRightFile.substr(28, 2) + "." + copyfindTable[i].copyfindPathOfRightFile.substr(31, 2) + "_" + normalrighttitle + "_" + regex_replace(copyfindTable[i].copyfindPathOfRightFile.substr(34), p, "$1");
		copyfindTable[i].nameOfRightPage = regex_replace(copyfindTable[i].copyfindPathOfRightFile.substr(23), u, "$1");
	}
}
void clearVectors() {
	wordCountTable.clear();
	copyfindTable.clear();
	comparisonsTable.clear();
	uniquePagesTable.clear();
}
void processDirectLinkComparisons() //creates a list of ancestor-descendent (directed link) pairs
{
	string UID; //unique article id
	int targetIndex;
	string BestMatch; //variable to indicate highest perfect match score
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
			if (comparisonsTable[j].laterPage.nameOfPage == UID) //if a target article in that line of the comparisons matches current unique article id
			{
				if (comparisonsTable[j].perfectMatchOfComparison > Score) //check to see if better perfect match has already been found; if not, proceed
				{
					if (comparisonsTable[j].earlierPage.yearOfPage == comparisonsTable[j].laterPage.yearOfPage && comparisonsTable[j].earlierPage.monthOfPage == comparisonsTable[j].laterPage.monthOfPage && comparisonsTable[j].earlierPage.dayOfPage == comparisonsTable[j].laterPage.dayOfPage)
					{
					}
					else if (comparisonsTable[j].earlierPage.yearOfPage > comparisonsTable[j].laterPage.yearOfPage || comparisonsTable[j].earlierPage.yearOfPage == comparisonsTable[j].laterPage.yearOfPage && comparisonsTable[j].earlierPage.monthOfPage > comparisonsTable[j].laterPage.monthOfPage || comparisonsTable[j].earlierPage.yearOfPage == comparisonsTable[j].laterPage.yearOfPage && comparisonsTable[j].earlierPage.monthOfPage == comparisonsTable[j].laterPage.monthOfPage && comparisonsTable[j].earlierPage.dayOfPage > comparisonsTable[j].laterPage.dayOfPage) //if source article is later than the target article
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
						if (comparisonsTable[j].earlierPage.yearOfPage > year || comparisonsTable[j].earlierPage.yearOfPage == year && comparisonsTable[j].earlierPage.monthOfPage > month || comparisonsTable[j].earlierPage.yearOfPage == year && comparisonsTable[j].earlierPage.monthOfPage == month && comparisonsTable[j].earlierPage.dayOfPage > day) //if current test is earlier than previous best match, replace entries with new data
						{
							BestMatch = comparisonsTable[j].earlierPage.normalisedNameOfPage; //set as best match for target
							Score = comparisonsTable[j].perfectMatchOfComparison; //set as new score
							bIsEarliest = true; //label target as earliest
							year = comparisonsTable[j].earlierPage.yearOfPage;  //set source year as year
							month = comparisonsTable[j].earlierPage.monthOfPage; //set source month as month
							day = comparisonsTable[j].earlierPage.dayOfPage; //set source day as day
						}
					}
					else if (comparisonsTable[j].earlierPage.yearOfPage > comparisonsTable[j].laterPage.yearOfPage || comparisonsTable[j].earlierPage.yearOfPage == comparisonsTable[j].laterPage.yearOfPage && comparisonsTable[j].earlierPage.monthOfPage > comparisonsTable[j].laterPage.monthOfPage || comparisonsTable[j].earlierPage.yearOfPage == comparisonsTable[j].laterPage.yearOfPage && comparisonsTable[j].earlierPage.monthOfPage == comparisonsTable[j].laterPage.monthOfPage && comparisonsTable[j].earlierPage.dayOfPage > comparisonsTable[j].laterPage.dayOfPage)//if current test is earlier than previous best match, replace entries with new data
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
void crossReferenceValuesInWordCountAndCopyfindTables() // combines British Library and Copyfind (average match wordcount) data
{
	int t = 0;
	size_t newT = t;
	for (int i = 0; i < size(copyfindTable); ++i) // iterate through cftable
	{
		for (size_t t = 0; t < size(wordCountTable); ++t)
		{
			if (copyfindTable[i].nameOfLeftPage == wordCountTable[t].wordCountTablePageName) // if the cfuid is the same as the bluid
			{
				copyfindTable[i].fullPageWordCountOfLeftPage = wordCountTable[t].wordCountTableWordCountOfPage; // add full wordcount
				copyfindTable[i].issueNameofLeftPage = wordCountTable[t].wordCountTableIssueName; // add issue name
				copyfindTable[i].copyfindFullWordCountOfLeftIssue = wordCountTable[t].wordCountTableFullWordCountOfIssue; // add issue wordcount
				newT = t;
				t = size(wordCountTable) - 1;
			}
		}
	}
}
void assignMaximumAverageWordCountValues() // creates a table of maximum wordcount values for each page and issue
{
	for (int i = 0; i < copyfindTable.size(); i++)
	{
		int testmaxval = copyfindTable[i].copyfindAverageMatch; // set test wordcount to i

		for (int j = 0; j < copyfindTable.size(); j++)
		{
			// go through cf table

			if (copyfindTable[i].normalisedNameOfLeftPage == copyfindTable[j].normalisedNameOfLeftPage)
			{
				// test cfam value against every other cfam value for same page

				if (testmaxval < copyfindTable[j].copyfindAverageMatch)
				{
					// if new value is bigger than test value, change test value to new value
					testmaxval = copyfindTable[j].copyfindAverageMatch;
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
			if (uniquePagesTable[k].nameOfLaterPage == copyfindTable[l].nameOfLeftPage)
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
