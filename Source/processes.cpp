#pragma once
#include "stdafx.h"
#include "processes.h"
#include "dateutil.h"
<<<<<<< HEAD
#include "coresettings.h"
#include "inputter.h"

vector<copyfindEntry> copyfindTable; //vector for raw Copyfind data
vector<wordCountTableEntry> wordCountTable; //vector for British Library wordcount data
vector<normalisedTitleReference> normalisedTitlesTable; //vector for normalised titles

void regexCopyfindTableTitles()
{
	for (int i = 0; i < copyfindTable.size(); i++)
=======

// Variables for makeCFTable
struct cfvalues {
	int cfpm; // perfect match value; pull from file
	int cflm; // lefthand match value; pull from file
	int cfrm; // righthand match value; pull from file
	int cfam; // average match value; proces in makeCFTable
	int cfmax; // maximum average match for page; process in processMaximumValues
	int cffpwc; // full-page word count of left file; pull from BLTable
	string cfissue; // issue of left file; pull from BL Table
	int cffiwc; // maximum average match for issue; process in processMaximumValues
	int cfissuewc; // full-issue word count of left file; pull from BL table
	string cfleft; // path to left file; process in makeCFTable
	string cfright; // path to right file; process in makeCFTable
	int cfly; // lefthand year; process in makeCFTable
	int cflmo; // lefthand month; process in makeCFTable
	int cfld; // lefthand day; process in makeCFTable
	string cflt; // lefthand title; process in makeCFTable
	string cflp; // lefthand page; process in makeCFTable
	string cfsluid; // unique id of lefthand file; pull from file
	string cfluid; // normalised unique id of lefthand file; processed from file
	int cfry; // righthand year; process in makeCFTable
	int cfrmo; // righthand month; process in makeCFTable
	int cfrd; // righthand day; process in makeCFTable
	string cfrt; // righthand title; process in makeCFTable
	string cfrp; // righthand page; process in makeCFTable
	string cfsruid; // unique id of righthand file; pull from file
	string cfruid; // normalised unique id of righthand file; processed from file
};
vector<cfvalues> cftable; //vector for raw Copyfind data

						  // Variables for makeBLTable
struct blcounts {
	string bluid; // full page id; pull from file
	double blwc;  // full page wc; pull from file
	string blissue; // full page issue; pull from file
	double blissuewc; // full issue wc; pull from file
};
vector<blcounts> bltable; //vector for British Library wordcount data

						  // Variables for makeNTTable
struct normTitle {
	string title; // BL title
	string ntitle; // Normalised title
};
vector<normTitle> normTitles; //vector for normalised titles

							  // Variables for makecomparisonsTable
struct Article //list all unique articles present in the input data
{
	string UI; //unique id of the article; pull from CFTable
	string SUI; //unique id of the article; pull from CFTable
	string Newspaper; //newspaper title; pull from CFTable
	int Year; //year of article; pull from CFTable
	int Month; //month of article; pull from CFTable
	int Day; //day of article; pull from CFTable
	string Page; //page of article; pull from CFTable
};
struct comparison //list all match sets for comparison
{
	int PM; //perfect match; pull from CFTable
	int OL; //left match; pull from CFTable
	int OR; //right match; pull from CFTable
	Article A;//struct with article metadata
	Article B;//struct with article metadata
};
vector<comparison> comparisons; //vector for comparison calculations
comparison Comp; //this is used to initialise new entries in the comparisons vector using push_back

				 // Variables for processDLcomparisons
struct results //final manifest; contains each target only once
{
	string UID; //unique id of target article; pull from cftable
	string sourceUID; //unique id of source article; pull from cftable
	bool bIsOriginal; //boolean indicating a successful source; process in dllinks
	bool bIsDeadEnd; //boolean indicating a dead-end source; process in dllinks
	double wc; // (reprints) maximum average word count of target page; pull from cftable
	double fpwc; // (whole) full-page word count of target page; pull from cftable
	string issue; // issue of target article; pull from cftable
	double iwc; // (reprints) maximum average word count of target issue; pull from cftable
	double fiwc; // (whole) full-issue word count of targe page; pull from cftable 
	double pageratio; // maximum average word count-to-page ratio; process in results
	double issueratio; // all maximum average word counts-to-issue ratio; process in results
};
vector<results> uniqueArticle; //vector containing the UI of all the unique articles that meet minimum requirements
results temp; //used to initialise new entries in the results vector using push_back

			  // Input Functions
void makeCFTable(string inputlocation, string syear, string smonth)
{
	int cfpm; // perfect match value
	int cflm; // lefthand match value
	int cfrm; // righthand match value
	string cfleft; // path to left file
	string cfright; // path to right file
	cfvalues empty;
	ifstream Data(inputlocation + "\\inputs\\rawmatchingreports\\" + syear + "_" + smonth + ".tsv");
	int i = -1;

	while (Data >> cfpm >> cflm >> cfrm >> cfleft >> cfright)
	{
		i += 1;
		cftable.push_back(empty);
		cftable[i].cfpm = cfpm;
		cftable[i].cflm = cflm;
		cftable[i].cfrm = cfrm;
		cftable[i].cfam = (cflm + cfrm) / 2;
		cftable[i].cfleft = cfleft;
		cftable[i].cfright = cfright;
	}
}
void makeBLTable(string inputlocation, string syear, string smonth, string syear2, string smonth2)
{
	blcounts empty;
	ifstream Data(inputlocation + "\\inputs\\bltables\\" + syear + "_" + smonth + ".txt");
	ifstream Data2(inputlocation + "\\inputs\\bltables\\" + syear2 + "_" + smonth2 + ".txt");
	string uid;
	double wc;
	string iid;
	double iwc;
	int i = -1;
	while (Data >> uid >> wc >> iid >> iwc)
	{
		i += 1;
		bltable.push_back(empty);
		bltable[i].bluid = uid;
		bltable[i].blwc = wc;
		bltable[i].blissue = iid;
		bltable[i].blissuewc = iwc;
	}
	while (Data2 >> uid >> wc >> iid >> iwc)
	{
		i += 1;
		bltable.push_back(empty);
		bltable[i].bluid = uid;
		bltable[i].blwc = wc;
		bltable[i].blissue = iid;
		bltable[i].blissuewc = iwc;
	}
}
void makeNTTable(string inputlocation)
{
	ifstream data(inputlocation + "\\inputs\\NormalisedTitlesns.tsv");
	string title = "";
	string ntitle = "";
	normTitle empty;
	int i = -1;

	while (data >> title >> ntitle)
	{
		i += 1;
		normTitles.push_back(empty);
		normTitles[i].title = title;
		normTitles[i].ntitle = ntitle;
	}
}

// Processing Functions
void regexCopyfind()
{
	for (int i = 0; i < size(cftable); i++)
>>>>>>> origin/master
	{
		regex t("([A-Za-z-,'&]+)_[A-Z_0-9]+.txt");
		regex p("[A-Za-z-,'&]+_([A-Z_0-9]+).txt");
		regex u("([0-9]{4}.[0-9]{2}.[0-9]{2}_[A-Za-z-,'&]+_[A-Z_0-9]+).txt");
		string normallefttitle = "";
		string templefttitle = "";
		string normalrighttitle = "";
		string temprighttitle = "";

<<<<<<< HEAD
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
=======
		cftable[i].cfly = stoi(cftable[i].cfleft.substr(25, 4));
		cftable[i].cflmo = stoi(cftable[i].cfleft.substr(30, 2));
		cftable[i].cfld = stoi(cftable[i].cfleft.substr(33, 2));
		templefttitle = regex_replace(cftable[i].cfleft.substr(36), t, "$1");
		for (int j = 0; j < size(normTitles); j++)
		{
			if (templefttitle == normTitles[j].title)
			{
				normallefttitle = normTitles[j].ntitle;
			}
		}
		cftable[i].cflt = normallefttitle;
		cftable[i].cflp = regex_replace(cftable[i].cfleft.substr(36), p, "$1");
		cftable[i].cfluid = cftable[i].cfleft.substr(25, 4) + "." + cftable[i].cfleft.substr(30, 2) + "." + cftable[i].cfleft.substr(33, 2) + "_" + normallefttitle + "_" + regex_replace(cftable[i].cfleft.substr(36), p, "$1");
		cftable[i].cfsluid = regex_replace(cftable[i].cfleft.substr(25), u, "$1");
		cftable[i].cfry = stoi(cftable[i].cfright.substr(25, 4));
		cftable[i].cfrmo = stoi(cftable[i].cfright.substr(30, 2));
		cftable[i].cfrd = stoi(cftable[i].cfright.substr(33, 2));
		temprighttitle = regex_replace(cftable[i].cfright.substr(36), t, "$1");
		for (int j = 0; j < size(normTitles); j++)
		{
			if (temprighttitle == normTitles[j].title)
			{
				normalrighttitle = normTitles[j].ntitle;
			}
		}
		cftable[i].cfrt = normalrighttitle;
		cftable[i].cfrp = regex_replace(cftable[i].cfright.substr(36), p, "$1");
		cftable[i].cfruid = cftable[i].cfright.substr(25, 4) + "." + cftable[i].cfright.substr(30, 2) + "." + cftable[i].cfright.substr(33, 2) + "_" + normalrighttitle + "_" + regex_replace(cftable[i].cfright.substr(36), p, "$1");
		cftable[i].cfsruid = regex_replace(cftable[i].cfright.substr(25), u, "$1");
	}
}
void makecomparisonsTable()
{
	int maxDaysBetween = 21; //up to 1 year maximum, otherwise change the comparison logic
	int OL_Tolerance = 90; //minimum left match
	int OR_Tolerance = 90; //minimum right match
	int PM_Tolerance = 160; //minimum overall or perfect match
	bool bUI_A_Done = false; //mark target as uncompared
	bool bUI_B_Done = false; //mark source as uncompared
	int scratch = 0;
	int j = 0;

	for (int i = 0; i < size(cftable); i++) //while data is available
	{
		if (cftable[i].cflt == cftable[i].cfrt) //do not include matches from same title
		{
		}
		else if (cftable[i].cfrm <= OR_Tolerance && cftable[i].cflm <= OL_Tolerance && cftable[i].cfrm + cftable[i].cflm <= PM_Tolerance) //remove small matches
		{
		}
		else if (cftable[i].cfly > cftable[i].cfry) //if the target year is later than the source year
		{
			if (cftable[i].cfly - cftable[i].cfry == 1) // and they are concurrent years
			{
				int A_Days = monthToDays(cftable[i].cfrm, isLeapYear(cftable[i].cfry)) + cftable[i].cfrd;//calculate numbers days into target year 
				bool bIsLeapYear = isLeapYear(cftable[i].cfly); //determine if the source year is a leap year
				int B_Days = monthToDays(cftable[i].cflmo, bIsLeapYear) + cftable[i].cfry; //calculate the number of days into source year
				if (bIsLeapYear)
					B_Days = 366 - B_Days; //calculate the number of days remaining in leap source year
				else
					B_Days = 365 - B_Days; //calculate the number of days remaining in non-leap source year
				if (A_Days + B_Days <= maxDaysBetween) //if days between is fewer than 200, proceed to print item in comparisons database
				{
					comparisons.push_back(Comp);
					comparisons[j].PM = cftable[i].cfpm; //perfect match
					comparisons[j].OL = cftable[i].cflm; //left match
					comparisons[j].OR = cftable[i].cfrm; //right match
					comparisons[j].A.UI = cftable[i].cfluid; //normalised unique id for target
					comparisons[j].A.SUI = cftable[i].cfsluid; //unique id for target
					comparisons[j].A.Newspaper = cftable[i].cflt; //target title
					comparisons[j].A.Year = cftable[i].cfly; //target year
					comparisons[j].A.Month = cftable[i].cflmo; //target month
					comparisons[j].A.Day = cftable[i].cfld; //target day
					comparisons[j].A.Page = cftable[i].cflp; //target page
					comparisons[j].B.UI = cftable[i].cfruid; //normalised unique id for source 
					comparisons[j].B.SUI = cftable[i].cfsruid; //unique id for source 
					comparisons[j].B.Newspaper = cftable[i].cfrt; //source title
					comparisons[j].B.Year = cftable[i].cfry; //source year
					comparisons[j].B.Month = cftable[i].cfrmo; //source month
					comparisons[j].B.Day = cftable[i].cfrd; //source day
					comparisons[j].B.Page = cftable[i].cfrp; //source page
					bUI_A_Done = false; //reset done variable
					bUI_B_Done = false; //reset done variable
					j++;
					for (int k = 0; k < size(uniqueArticle); ++k)//for every item in the unique id list
					{
						if (uniqueArticle[k].UID == cftable[i].cfluid) //if target article is already in unique id list
							bUI_A_Done = true; //mark target article as checked
						if (uniqueArticle[k].UID == cftable[i].cfruid) //if source article is already in unique id list
							bUI_B_Done = true; //mark source article as checked
					}
					if (!bUI_A_Done) //if target article is not marked as checked
					{
						scratch = size(uniqueArticle);
						uniqueArticle.push_back(temp);
						uniqueArticle[scratch].UID = cftable[i].cfluid; //add target article to unique id list
					}
					if (!bUI_B_Done) //if source article is not marked as checked
					{
						scratch = size(uniqueArticle);
						uniqueArticle.push_back(temp);
						uniqueArticle[scratch].UID = cftable[i].cfruid; //add source article to unique id list
					}
				}
			}
		}
		else if (cftable[i].cflmo > cftable[i].cfrmo || cftable[i].cflmo == cftable[i].cfrmo && cftable[i].cfld >= cftable[i].cfrd) //if they are the same year and the target month is later than the source month, or they are the same month and the target day is on or later than the source day
		{
			int A_Days = monthToDays(cftable[i].cflmo, isLeapYear(cftable[i].cfly)) + cftable[i].cfld; //calculate days in target year so far
			int B_Days = monthToDays(cftable[i].cfrmo, isLeapYear(cftable[i].cfry)) + cftable[i].cfrd; //calculate days in source year so far
			if (A_Days - B_Days <= maxDaysBetween) //calculate days between articles to see if equal or under Max Days; if so, proceed
			{
				comparisons.push_back(Comp); //add to comparisons list
				comparisons[j].PM = cftable[i].cfpm; //perfect match
				comparisons[j].OL = cftable[i].cflm; //left match
				comparisons[j].OR = cftable[i].cfrm; //right match
				comparisons[j].A.UI = cftable[i].cfluid; //unique id for target
				comparisons[j].A.Newspaper = cftable[i].cflt; //target title
				comparisons[j].A.Year = cftable[i].cfly; //target year
				comparisons[j].A.Month = cftable[i].cflmo; //target month
				comparisons[j].A.Day = cftable[i].cfld; //target day
				comparisons[j].A.Page = cftable[i].cflp; //target page
				comparisons[j].B.UI = cftable[i].cfruid; //unique id for source 
				comparisons[j].B.Newspaper = cftable[i].cfrt; //source title
				comparisons[j].B.Year = cftable[i].cfry; //source year
				comparisons[j].B.Month = cftable[i].cfrmo; //source month
				comparisons[j].B.Day = cftable[i].cfrd; //source day
				comparisons[j].B.Page = cftable[i].cfrp; //source page
				bUI_A_Done = false; //reset done variable
				bUI_B_Done = false; //reset done variable
				j++;
				for (int l = 0; l < size(uniqueArticle); ++l) //for every item in the unique id list
				{
					if (uniqueArticle[l].UID == cftable[i].cfluid) //if target article is already in unique id list
						bUI_A_Done = true; //mark target article as checked
					if (uniqueArticle[l].UID == cftable[i].cfruid) //if target article is already in unique id list
						bUI_B_Done = true; //mark target article as checked
				}
				if (!bUI_A_Done) //if source article is not marked as checked
				{
					scratch = size(uniqueArticle);
					uniqueArticle.push_back(temp);
					uniqueArticle[scratch].UID = cftable[i].cfluid; //add target article to unique id list
				}
				if (!bUI_B_Done) //if source article is not marked as checked
				{
					scratch = size(uniqueArticle);
					uniqueArticle.push_back(temp);
					uniqueArticle[scratch].UID = cftable[i].cfruid; //add source article to unique id list
				}
			}
		}
	}
}
void clearVectors() {
	bltable.clear();
	cftable.clear();
	comparisons.clear();
	uniqueArticle.clear();
}
void processDLcomparisons() //creates a list of ancestor-descendent (directed link) pairs
>>>>>>> origin/master
{
	string UID; //unique article id
	int targetIndex;
	string BestMatch; //variable to indicate highest perfect match score
	int Score; //perfect match score
	bool bIsEarliest;

<<<<<<< HEAD
	for (int it = 0; it < size(uniquePagesTable); ++it) //for each unique article id
	{
		UID = uniquePagesTable[it].nameOfLaterPage; //set UID to unique article id
=======
	for (int it = 0; it < size(uniqueArticle); ++it) //for each unique article id
	{
		UID = uniqueArticle[it].UID; //set UID to unique article id
>>>>>>> origin/master
		targetIndex = 0; //set targetIndex to null
		BestMatch = ""; //set BestMatch to null
		Score = 0; //set Score to null
		bIsEarliest = false; //boolean to indicate if it is earliest match
		int year = 0; //set year to null
		int month = 0; //set month to null
		int day = 0; //set day to null
<<<<<<< HEAD
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
=======
		for (int it2 = 0; it2 < size(comparisons); ++it2) //go through the comparisons list
		{
			if (comparisons[it2].A.UI == UID) //if a target article in that line of the comparisons matches current unique article id
			{
				if (comparisons[it2].PM > Score) //check to see if better perfect match has already been found; if not, proceed
				{
					if (comparisons[it2].B.Year == comparisons[it2].A.Year && comparisons[it2].B.Month == comparisons[it2].A.Month && comparisons[it2].B.Day == comparisons[it2].A.Day)
					{
					}
					else if (comparisons[it2].B.Year > comparisons[it2].A.Year || comparisons[it2].B.Year == comparisons[it2].A.Year && comparisons[it2].B.Month > comparisons[it2].A.Month || comparisons[it2].B.Year == comparisons[it2].A.Year && comparisons[it2].B.Month == comparisons[it2].A.Month && comparisons[it2].B.Day > comparisons[it2].A.Day) //if source article is later than the target article
					{
						BestMatch = comparisons[it2].B.UI; //unique id of source
						Score = comparisons[it2].PM; //set score as current best score
						bIsEarliest = true; //label target as earliest
						year = comparisons[it2].B.Year;  //set source year as year
						month = comparisons[it2].B.Month; //set source month as month
						day = comparisons[it2].B.Day; //set source day as day
					}
					else if (!bIsEarliest) //if no match has been found yet, print
					{
						BestMatch = comparisons[it2].B.UI; //unique id of source
						Score = comparisons[it2].PM; //set score as current best score
						bIsEarliest = false; //allows it to keep searching for better matches
						year = comparisons[it2].B.Year; // set source year as year
						month = comparisons[it2].B.Month; //set source month as month
						day = comparisons[it2].B.Day; //set source day as day
					}
				}
				if (comparisons[it2].PM == Score) //check to see if perfect match is the same as current source; if so, proceed
				{
					if (bIsEarliest) //if bIsEarliest is set to true; shouldn't be
					{
						if (comparisons[it2].B.Year > year || comparisons[it2].B.Year == year && comparisons[it2].B.Month > month || comparisons[it2].B.Year == year && comparisons[it2].B.Month == month && comparisons[it2].B.Day > day) //if current test is earlier than previous best match, replace entries with new data
						{
							BestMatch = comparisons[it2].B.UI; //set as best match for target
							Score = comparisons[it2].PM; //set as new score
							bIsEarliest = true; //label target as earliest
							year = comparisons[it2].B.Year;  //set source year as year
							month = comparisons[it2].B.Month; //set source month as month
							day = comparisons[it2].B.Day; //set source day as day
						}
					}
					else if (comparisons[it2].B.Year > comparisons[it2].A.Year || comparisons[it2].B.Year == comparisons[it2].A.Year && comparisons[it2].B.Month > comparisons[it2].A.Month || comparisons[it2].B.Year == comparisons[it2].A.Year && comparisons[it2].B.Month == comparisons[it2].A.Month && comparisons[it2].B.Day > comparisons[it2].A.Day)//if current test is earlier than previous best match, replace entries with new data
					{
						BestMatch = comparisons[it2].B.UI; //unique id of source
						Score = comparisons[it2].PM; //set score as current best score
						bIsEarliest = false; //allows it to keep searching for better matches
						year = comparisons[it2].B.Year; // set source year as year
						month = comparisons[it2].B.Month; //set source month as month
						day = comparisons[it2].B.Day; //set source day as day
>>>>>>> origin/master
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
<<<<<<< HEAD
			uniquePagesTable[it].bHasNoDescendents = true; //label as DeadEnd
			uniquePagesTable[it].nameOfEarlierPage = BestMatch;
			uniquePagesTable[it].bHasDescendents = bIsEarliest;
		}
		else //if target is not labeled as earliest
		{
			uniquePagesTable[it].nameOfEarlierPage = BestMatch;
			uniquePagesTable[it].bHasDescendents = bIsEarliest;
=======
			uniqueArticle[it].bIsDeadEnd = true; //label as DeadEnd
			uniqueArticle[it].sourceUID = BestMatch;
			uniqueArticle[it].bIsOriginal = bIsEarliest;
		}
		else //if target is not labeled as earliest
		{
			uniqueArticle[it].sourceUID = BestMatch;
			uniqueArticle[it].bIsOriginal = bIsEarliest;
>>>>>>> origin/master
		}
	}

}
<<<<<<< HEAD
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
=======
void crossReferenceValues() // combines British Library and Copyfind (average match wordcount) data
{
	int t = 0;
	int newT = t;
	for (int i = 0; i < size(cftable); ++i) // iterate through cftable
	{
		for (t = 0; t < size(bltable); ++t)
		{
			if (cftable[i].cfsluid == bltable[t].bluid) // if the cfuid is the same as the bluid
			{
				cftable[i].cffpwc = bltable[t].blwc; // add full wordcount
				cftable[i].cfissue = bltable[t].blissue; // add issue name
				cftable[i].cfissuewc = bltable[t].blissuewc; // add issue wordcount
				newT = t;
				t = size(bltable) - 1;
>>>>>>> origin/master
			}
		}
	}
}
<<<<<<< HEAD
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
=======
void processMaximumValues() // creates a table of maximum wordcount values for each page and issue
{
	for (int i = 0; i < size(cftable); ++i) // setting max value per page
	{
		string testmaxvalp = cftable[i].cfluid; // set test page uid
		double testmaxval = cftable[i].cfam; // set test wc
		string testmaxvali = cftable[i].cfissue; // set test issue uid

		if (i < 40)
		{
			for (int t = 0; t < i + 33; ++t)
			{
				if (cftable[t].cfluid == cftable[i].cfluid && cftable[t].cfam > testmaxval)
					// if the first id is the same as the second
					// and the word count is greater than the test value
				{
					testmaxvalp = cftable[t].cfluid;
					testmaxval = cftable[t].cfam;
					testmaxvali = cftable[t].cfissue;
				}
			}
			cftable[i].cfmax = testmaxval; // set the page's max value as the test value
		}
		else
		{
			for (int t = i - 33; t < i + 33 && t< size(cftable); ++t)
			{
				if (cftable[t].cfluid == cftable[i].cfluid && cftable[t].cfam > testmaxval)
					// if the first id is the same as the second
					// and the word count is greater than the test value
				{
					testmaxval = cftable[t].cfam;
					testmaxvalp = cftable[t].cfluid;
					testmaxvali = cftable[t].cfissue;
				}
			}
		}
		cftable[i].cfmax = testmaxval; // set the page's max value as the test value
	}
	for (int i = 0; i < size(cftable); ++i) // setting max value per page
	{
		double testissuesum = 0; // set test issue wc

		if (i < 40)
		{
			for (int t = 0; t < i + 33; ++t)
			{
				if (cftable[t].cfissue == cftable[i].cfissue)
				{
					testissuesum += cftable[t].cfmax;
				}
			}
			cftable[i].cffiwc = testissuesum; // set the issue's max value as the test value
		}
		else
		{
			for (int t = i - 33; t < i + 33 && t < size(cftable); ++t)
			{
				if (cftable[t].cfissue == cftable[i].cfissue)
				{
					testissuesum += cftable[t].cfmax;
				}
			}
			cftable[i].cffiwc = testissuesum; // set the issue's max value as the test value
		}
	}
	for (int i = 0; i < size(uniqueArticle); ++i) // go through unique targets
	{
		for (int j = 0; j < size(cftable); ++j) // go through copyfind table
		{
			if (cftable[j].cfluid == uniqueArticle[i].UID) // transfer values to uniqueArticle vector
			{
				uniqueArticle[i].issue = cftable[j].cfissue;
				uniqueArticle[i].iwc = cftable[j].cffiwc;
				uniqueArticle[i].fiwc = cftable[j].cfissuewc;
				uniqueArticle[i].issueratio = uniqueArticle[i].iwc / uniqueArticle[i].fiwc;
				uniqueArticle[i].wc = cftable[j].cfmax;
				uniqueArticle[i].fpwc = cftable[j].cffpwc;
				uniqueArticle[i].pageratio = uniqueArticle[i].wc / uniqueArticle[i].fpwc;


				//cout << endl << i << ":" << endl;
				//cout << uniqueArticle[i].UID << " " << uniqueArticle[i].issue << " " << uniqueArticle[i].iwc << " " << uniqueArticle[i].fiwc << " " << uniqueArticle[i].issueratio << " " << uniqueArticle[i].wc << " " << uniqueArticle[i].fpwc << " " << uniqueArticle[i].pageratio << endl;
			}
		}
	}
}

// Writing Functions
void writeComparisonTable(string inputlocation, string syear, string smonth)
{
	string data = "";

	ofstream file(inputlocation + "\\outputs\\memes\\" + syear + "_" + smonth + ".tsv"); //print raw comparison table

	for (int i = 0; i < size(comparisons); ++i)
	{
		std::transform(comparisons[i].A.Newspaper.begin(), comparisons[i].A.Newspaper.end(), comparisons[i].A.Newspaper.begin(), [](char ch) {return ch == '|' ? ' ' : ch; });
		std::transform(comparisons[i].B.Newspaper.begin(), comparisons[i].B.Newspaper.end(), comparisons[i].B.Newspaper.begin(), [](char ch) {return ch == '|' ? ' ' : ch; });
		data = data + comparisons[i].A.UI.substr(0, 4) + "\t" + comparisons[i].A.UI.substr(5, 2) + "\t" + comparisons[i].A.UI.substr(8, 2) + "\t";
		data = data + comparisons[i].A.Newspaper + "\t" + comparisons[i].A.Page + "\t";
		data = data + comparisons[i].B.UI.substr(0, 4) + "\t" + comparisons[i].B.UI.substr(5, 2) + "\t" + comparisons[i].B.UI.substr(8, 2) + "\t";
		data = data + comparisons[i].B.Newspaper + "\t" + comparisons[i].B.Page + "\n";
	}
	file << data;
	return;
}
void writeDirectedLinksTables(string inputlocation, string syear, string smonth)
{
	string dldata = "";
	string dedata = "";
	regex t("([A-Za-z-,'&]+)_[A-Z0-9_]{4}");
	regex p("[A-Za-z-,'&]+_([A-Z0-9_]{4})");

	ofstream dlfile(inputlocation + "\\outputs\\directedlinks\\" + syear + "_" + smonth + ".tsv"); //print ancestor-descendent pairs into file
	ofstream defile(inputlocation + "\\outputs\\evolutionarydeadends\\" + syear + "_" + smonth + ".tsv"); //print list of evolutionary dead-ends

	for (int i = 0; i < size(uniqueArticle); ++i)
	{
		if (!uniqueArticle[i].bIsDeadEnd)
		{
			dldata = dldata + uniqueArticle[i].UID.substr(0, 4) + "\t" + uniqueArticle[i].UID.substr(5, 2) + "\t" + uniqueArticle[i].UID.substr(8, 2) + "\t";
			dldata = dldata + regex_replace(uniqueArticle[i].UID.substr(11), t, "$1") + "\t" + regex_replace(uniqueArticle[i].UID.substr(11), p, "$1") + "\t";
			dldata = dldata + uniqueArticle[i].sourceUID.substr(0, 4) + "\t" + uniqueArticle[i].sourceUID.substr(5, 2) + "\t" + uniqueArticle[i].sourceUID.substr(8, 2) + "\t";
			dldata = dldata + regex_replace(uniqueArticle[i].sourceUID.substr(11), t, "$1") + "\t" + regex_replace(uniqueArticle[i].sourceUID.substr(11), p, "$1") + "\n";
		}
	}
	for (int i = 0; i < size(uniqueArticle); ++i)
	{
		if (uniqueArticle[i].bIsDeadEnd)
		{
			dedata = dedata + uniqueArticle[i].UID.substr(0, 4) + "\t" + uniqueArticle[i].UID.substr(5, 2) + "\t" + uniqueArticle[i].UID.substr(8, 2) + "\t";
			dedata = dedata + regex_replace(uniqueArticle[i].UID.substr(11, uniqueArticle[i].UID.length()), t, "$1") + "\t" + regex_replace(uniqueArticle[i].UID.substr(11, uniqueArticle[i].UID.length()), p, "$1") + "\n";
		}
	}
	dlfile << dldata;
	defile << dedata;
	return;
}
void writeMaxMatchList(string inputlocation, string syear, string smonth)
{
	string outputraw = (inputlocation + "\\outputs\\wordcounts\\" + syear + "_" + smonth + ".tsv");
	string lines = "";
	ofstream matchfile(outputraw);

	int m = 0;

	while (m < size(uniqueArticle))
	{
		if (!uniqueArticle[m].bIsDeadEnd)
		{
			lines = lines + uniqueArticle[m].UID + "\t" + to_string(int(uniqueArticle[m].wc)) + "\n";
		}
		m = m + 1;
	}
	matchfile << lines;
}
void writePagePercentage(string inputlocation, string syear, string smonth)
{
	string lines = "";
	ofstream file(inputlocation + "\\outputs\\pagepercentage\\" + syear + "_" + smonth + ".tsv");
	string errorlines = "";
	ofstream errorfile(inputlocation + "\\outputs\\pagepercentage\\error\\" + syear + "_" + smonth + ".tsv");

	for (int i = 0; i < size(uniqueArticle); ++i)
	{
		if (uniqueArticle[i].sourceUID != "")
		{
			if (uniqueArticle[i].pageratio >= 1 || uniqueArticle[i].pageratio <= 0)
			{
				if (uniqueArticle[i].UID != "")
				{
					errorlines += uniqueArticle[i].UID + "\n";
				}
			}
			else
			{
				if (uniqueArticle[i].UID != "")
				{
					lines += uniqueArticle[i].UID + "\t" + to_string(uniqueArticle[i].pageratio) + "\n";
				}
			}
		}
	}
	file << lines;
	errorfile << errorlines;
}
void writeIssuePercentage(string inputlocation, string syear, string smonth)
{
	string lines = "";
	ofstream file(inputlocation + "\\outputs\\issuepercentage\\" + syear + "_" + smonth + ".tsv");
	string errorlines = "";
	ofstream errorfile(inputlocation + "\\outputs\\issuepercentage\\error\\" + syear + "_" + smonth + ".tsv");

	for (int i = 0; i < size(uniqueArticle); ++i)
	{
		if (uniqueArticle[i].sourceUID != "")
		{
			if (i > 0)
			{
				if (uniqueArticle[i].issue != uniqueArticle[i - 1].issue)
				{
					if (uniqueArticle[i].issueratio >= 1 || uniqueArticle[i].issueratio <= 0 && uniqueArticle[i].issue != "")
					{
						if (uniqueArticle[i].issue != "")
						{
							errorlines += uniqueArticle[i].issue + "\n";
						}
					}
					else
					{
						if (uniqueArticle[i].issue != "")
						{
							lines += uniqueArticle[i].issue + "\t" + to_string(uniqueArticle[i].issueratio) + "\n";
						}
					}
				}
			}
			else
			{
				if (uniqueArticle[i].issueratio >= 1 || uniqueArticle[i].issueratio <= 0)
				{
					if (uniqueArticle[i].issue != "")
					{
						stringstream errors;
						errors << uniqueArticle[i].issue;
						errorlines += errors.str();
						errorlines += "\n";
					}
				}
				else
				{
					stringstream ss;
					ss << uniqueArticle[i].issue << "\t" << uniqueArticle[i].issueratio;
					lines += ss.str();
					lines += "\n";
				}
			}
		}
	}
	file << lines;
	errorfile << errorlines;
}
void writeTitlePagePercentage(string inputlocation, string syear, string smonth)
{
	ifstream data(inputlocation + "\\inputs\\NormalisedTitlesns.tsv");
	string title = "";
	string ntitle = "";

	while (data >> title >> ntitle)
	{
		string lines = "";
		ofstream file(inputlocation + "\\outputs\\titles\\pagepercentage\\" + ntitle + "\\" + syear + "_" + smonth + ".tsv");
		string errorlines = "";
		ofstream errorfile(inputlocation + "\\outputs\\titles\\pagepercentage\\error\\" + ntitle + "\\" + syear + "_" + smonth + ".tsv");

		for (int i = 0; i < size(uniqueArticle); ++i)
		{
			if (uniqueArticle[i].sourceUID != "")
			{
				if (uniqueArticle[i].UID.find(ntitle) != string::npos)
				{
					if (uniqueArticle[i].pageratio >= 1 || uniqueArticle[i].pageratio <= 0 && uniqueArticle[i].UID != "")
					{
						if (uniqueArticle[i].UID != "")
						{
							errorlines += uniqueArticle[i].UID + "\n";
						}
					}
					else
					{
						if (uniqueArticle[i].UID != "")
						{
							lines += uniqueArticle[i].UID + "\t" + to_string(uniqueArticle[i].pageratio) + "\n";
						}
					}
				}
			}
		}
		file << lines;
		errorfile << errorlines;
	}
}
void writeTitleIssuePercentage(string inputlocation, string syear, string smonth)
{
	ifstream data(inputlocation + "\\inputs\\NormalisedTitlesns.tsv");
	string title = "";
	string ntitle = "";

	while (data >> title >> ntitle)
	{
		string lines = "";
		ofstream file(inputlocation + "\\outputs\\titles\\issuepercentage\\" + ntitle + "\\" + syear + "_" + smonth + ".tsv");
		string errorlines = "";
		ofstream errorfile(inputlocation + "\\outputs\\titles\\issuepercentage\\" + ntitle + "\\" + syear + "_" + smonth + ".tsv");
		for (int i = 0; i < size(uniqueArticle); ++i)
		{
			if (uniqueArticle[i].sourceUID != "")
			{

				if (uniqueArticle[i].UID.find(ntitle) != string::npos)
				{
					if (i > 0)
					{
						if (uniqueArticle[i].issue != uniqueArticle[i - 1].issue)
						{
							if (uniqueArticle[i].issueratio >= 1 || uniqueArticle[i].issueratio <= 0 && uniqueArticle[i].issue != "")
							{
								if (uniqueArticle[i].issue != "")
								{
									errorlines += uniqueArticle[i].issue + "\n";
								}
							}
							else
							{
								if (uniqueArticle[i].issue != "")
								{
									lines += uniqueArticle[i].issue + "\t" + to_string(uniqueArticle[i].issueratio) + "\n";
								}
							}
						}
					}
					else
					{
						if (uniqueArticle[i].issueratio >= 1 || uniqueArticle[i].issueratio <= 0)
						{
							if (uniqueArticle[i].issue != "")
							{
								stringstream errors;
								errors << uniqueArticle[i].issue;
								errorlines += errors.str();
								errorlines += "\n";
							}
						}
						else
						{
							stringstream ss;
							ss << uniqueArticle[i].issue << "\t" << uniqueArticle[i].issueratio;
							lines += ss.str();
							lines += "\n";
						}
					}
				}
			}
		}

		file << lines;
		errorfile << errorlines;
	}
}
>>>>>>> origin/master
