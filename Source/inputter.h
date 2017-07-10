#pragma once
#include "coresettings.h"

class inputter
{
public:
	// Variables

	std::string inputFileStructureLocation;
	std::string stringOfYear;
	std::string stringOfMonth;
	std::string stringOfPreviousYear;
	std::string stringOfPreviousMonth;
	std::string stringOfSubsequentYear;
	std::string stringOfSubsequentMonth;

	// Structs
	struct copyfindEntry {
		int copyfindPerfectMatch; // pull from copyfind file
		int copyfindLefthandMatch; // pull from copyfind file
		int copyfindRighthandMatch; // pull from copyfind file
		int copyfindAverageMatch; // process in makeCFTable
		int copyfindMaximumWordCount; // process in processMaximumValues
		double fullPageWordCountOfLeftPage; // pull from wordCountTable
		std::string issueNameofLeftPage; // pull from wordCountTable
		int copyfindCombinedAverageWordCountForLeftIssue; // process in processMaximumValues
		double copyfindFullWordCountOfLeftIssue; // pull from BL table
		std::string copyfindPathOfLeftFile; // pull from copyfind file
		std::string copyfindPathOfRightFile; // pull from copyfind file
		int yearOfLeftPage; // process in makeCFTable
		int monthOfLeftPage; // process in makeCFTable
		int dayOfLeftPage; // process in makeCFTable
		std::string titleOfLeftPage; // process in makeCFTable
		std::string pageNumberOfLeftPage; // process in makeCFTable
		std::string nameOfLeftPage; // pull from file
		std::string normalisedNameOfLeftPage; // processed from file
		int yearOfRightPage; // process in makeCFTable
		int monthOfRightPage; // process in makeCFTable
		int dayOfRightPage; // process in makeCFTable
		std::string titleOfRightPage; // process in makeCFTable
		std::string pageOfRightPage; // process in makeCFTable
		std::string nameOfRightPage; // pull from file
		std::string normalisedNameOfRightPage; // normalised unique id of righthand file; processed from file
	};
	struct wordCountTableEntry {
		std::string wordCountTablePageName; // full page id; pull from file
		double wordCountTableWordCountOfPage;  // full page wc; pull from file
		std::string wordCountTableIssueName; // full page issue; pull from file
		double wordCountTableFullWordCountOfIssue; // full issue wc; pull from file
	};
	struct normalisedTitleReference {
		std::string title; // BL title
		std::string normalisedTitle; // Normalised title
	};

	struct articleEntry //list all unique articles present in the input data
	{
		std::string normalisedNameOfPage; // pull from copyfind table
		std::string nameOfPage; // pull from copyfind table
		std::string titleOfPage; // pull from copyfind table
		int yearOfPage; // pull from copyfind table
		int monthOfPage; // pull from copyfind table
		int dayOfPage;  // pull from copyfind table
		std::string pageNumberOfPage;  // pull from copyfind table
	};
	struct comparisonEntry // displays a pair of pages that has been compared
	{
		int perfectMatchOfComparison;  // pull from copyfind table
		int leftHandMatchOfComparison;  // pull from copyfind table
		int rightHandMatchOfComparison;  // pull from copyfind table
		articleEntry laterPage; // data from copyfind table
		articleEntry earlierPage; // data  from copyfind table
	};
	struct uniquePageEntry //final manifest; contains each target only once
	{
		std::string nameOfLaterPage;  // pull from copyfind table
		std::string nameOfEarlierPage;   // pull from copyfind table
		bool bHasDescendents;   // pull from copyfind table
		bool bHasNoDescendents;   // pull from copyfind table
		double maximumAverageWordCountForReprintsOnLaterPage; // (reprints) maximum average word count of target page; pull from cftable
		double fullWordCountofLaterPage; // (whole) full-page word count of target page; pull from cftable via wordCountTable
		std::string nameOfIssue; // issue of target article; pull from cftable
		double combinedAverageWordCountForIssue; // (reprints) maximum average word count of target issue; pull from cftable
		double fullWordCountOfIssue; // (whole) full-issue word count of targe page; pull from cftable 
		double percentageOfReprintedMaterialOnPage; // maximum average word count-to-page ratio; process in results
		double percentageOfReprintedMaterialInIssue; // all maximum average word counts-to-issue ratio; process in results
	};

	// Vectors
	std::vector<comparisonEntry> comparisonsTable;
	comparisonEntry emptyComparison;

	std::vector<uniquePageEntry> uniquePagesTable;
	uniquePageEntry emptyPage;

	std::vector<copyfindEntry> copyfindTable;
	std::vector<wordCountTableEntry> wordCountTable;
	std::vector<normalisedTitleReference> normalisedTitlesTable;

	// inputter
	void makeCopyFindTable()
	{
		//std::cout << inputFileStructureLocation << std::endl;
		int inputPerfectMatch;
		int inputLeftMatch;
		int inputRightMatch;
		std::string inputPathOfLeftFile;
		std::string inputPathOfRightFile;
		copyfindEntry empty;
		std::ifstream dateForPreviousMonth(inputFileStructureLocation
			+ "\\inputs\\rawmatchingreports\\"
			+ stringOfPreviousYear
			+ "_"
			+ stringOfPreviousMonth
			+ ".txt");
		std::ifstream dataForCurrentMonth(inputFileStructureLocation
			+ "\\inputs\\rawmatchingreports\\"
			+ stringOfYear
			+ "_"
			+ stringOfMonth + ".txt");
		int i = -1;

		while (dateForPreviousMonth >> inputPerfectMatch >> inputLeftMatch >> inputRightMatch >> inputPathOfLeftFile >> inputPathOfRightFile)
		{
			int yearOfLeftPage = stoi(inputPathOfLeftFile.substr(23, 4));
			int monthOfLeftPage = stoi(inputPathOfLeftFile.substr(28, 2));
			int dayOfLeftPage = stoi(inputPathOfLeftFile.substr(31, 2));
			int yearOfRightPage = stoi(inputPathOfRightFile.substr(23, 4));
			int monthOfRightPage = stoi(inputPathOfRightFile.substr(28, 2));
			int dayOfRightPage = stoi(inputPathOfRightFile.substr(31, 2));

			if // if lefthand date is later than right hand date
				(
					yearOfLeftPage > yearOfRightPage
					||
					monthOfLeftPage > monthOfRightPage&&
					yearOfLeftPage == monthOfLeftPage
					||
					dayOfLeftPage > dayOfRightPage&&
					monthOfLeftPage == monthOfRightPage&&
					yearOfLeftPage == monthOfLeftPage
					)
			{
				// do as normal
				i += 1;
				copyfindTable.push_back(empty);
				copyfindTable[i].copyfindPerfectMatch = inputPerfectMatch;
				copyfindTable[i].copyfindLefthandMatch = inputLeftMatch;
				copyfindTable[i].copyfindRighthandMatch = inputRightMatch;
				copyfindTable[i].copyfindAverageMatch = (inputLeftMatch + inputRightMatch) / 2;
				copyfindTable[i].copyfindPathOfLeftFile = inputPathOfLeftFile;
				copyfindTable[i].copyfindPathOfRightFile = inputPathOfRightFile;
			}
			else // if righthand date is earlier than left hand date
			{
				// swap input file paths
				i += 1;
				copyfindTable.push_back(empty);
				copyfindTable[i].copyfindPerfectMatch = inputPerfectMatch;
				copyfindTable[i].copyfindLefthandMatch = inputLeftMatch;
				copyfindTable[i].copyfindRighthandMatch = inputRightMatch;
				copyfindTable[i].copyfindAverageMatch = (inputLeftMatch + inputRightMatch) / 2;
				copyfindTable[i].copyfindPathOfLeftFile = inputPathOfRightFile;
				copyfindTable[i].copyfindPathOfRightFile = inputPathOfLeftFile;
			}
		}

		while (dataForCurrentMonth >> inputPerfectMatch >> inputLeftMatch >> inputRightMatch >> inputPathOfLeftFile >> inputPathOfRightFile)
		{
			std::string yearOfLeftPage = inputPathOfLeftFile.substr(23, 4);
			std::string monthOfLeftPage = inputPathOfLeftFile.substr(28, 2);
			std::string dayOfLeftPage = inputPathOfLeftFile.substr(31, 2);
			std::string yearOfRightPage = inputPathOfRightFile.substr(23, 4);
			std::string monthOfRightPage = inputPathOfRightFile.substr(28, 2);
			std::string dayOfRightPage = inputPathOfRightFile.substr(31, 2);


			if // if lefthand date is earlier than right hand date
				(
				(stoi(dayOfLeftPage) < stoi(dayOfRightPage) &&
					stoi(monthOfLeftPage) == stoi(monthOfRightPage) &&
					stoi(yearOfLeftPage) == stoi(yearOfRightPage))
					||
					(stoi(monthOfLeftPage) < stoi(monthOfRightPage) &&
						stoi(yearOfLeftPage) == stoi(yearOfRightPage))
					||
					(stoi(yearOfLeftPage) < stoi(yearOfRightPage))
					)
			{
				// swap input file paths then do as normal
				i += 1;
				copyfindTable.push_back(empty);
				copyfindTable[i].copyfindPerfectMatch = inputPerfectMatch;
				copyfindTable[i].copyfindLefthandMatch = inputLeftMatch;
				copyfindTable[i].copyfindRighthandMatch = inputRightMatch;
				copyfindTable[i].copyfindAverageMatch = (inputLeftMatch + inputRightMatch) / 2;
				copyfindTable[i].copyfindPathOfLeftFile = inputPathOfRightFile;
				copyfindTable[i].copyfindPathOfRightFile = inputPathOfLeftFile;
			}
			else // if righthand date is later than left hand date
			{
				// do as normal
				i += 1;
				copyfindTable.push_back(empty);
				copyfindTable[i].copyfindPerfectMatch = inputPerfectMatch;
				copyfindTable[i].copyfindLefthandMatch = inputLeftMatch;
				copyfindTable[i].copyfindRighthandMatch = inputRightMatch;
				copyfindTable[i].copyfindAverageMatch = (inputLeftMatch + inputRightMatch) / 2;
				copyfindTable[i].copyfindPathOfLeftFile = inputPathOfLeftFile;
				copyfindTable[i].copyfindPathOfRightFile = inputPathOfRightFile;
			}
		}

	}
	void makeWordCountTable(std::string inputFileStructureLocation, std::string stringOfCurrentYear, std::string stringOfCurrentMonth, std::string stringOfSubsequentYear, std::string stringOfSubsequentMonth, std::string stringOfPreviousYear, std::string stringOfPreviousMonth)
	{
		wordCountTableEntry empty;
		std::ifstream dataOfPreviousMonth(inputFileStructureLocation + "\\inputs\\wctables\\" + stringOfPreviousYear + "_" + stringOfPreviousMonth + ".tsv");
		std::ifstream dataOfCurrentMonth(inputFileStructureLocation + "\\inputs\\wctables\\" + stringOfCurrentYear + "_" + stringOfCurrentMonth + ".tsv");
		std::ifstream Data2(inputFileStructureLocation + "\\inputs\\wctables\\" + stringOfSubsequentYear + "_" + stringOfSubsequentMonth + ".tsv");
		std::string inputNameOfPage;
		double inputWordCountOfPage;
		std::string inputNameOfIssue;
		double inputWordCountOfIssue;
		int i = -1;
		while (dataOfPreviousMonth >> inputNameOfPage >> inputWordCountOfPage >> inputNameOfIssue >> inputWordCountOfIssue)
		{
			i += 1;
			wordCountTable.push_back(empty);
			wordCountTable[i].wordCountTablePageName = inputNameOfPage;
			wordCountTable[i].wordCountTableWordCountOfPage = inputWordCountOfPage;
			wordCountTable[i].wordCountTableIssueName = inputNameOfIssue;
			wordCountTable[i].wordCountTableFullWordCountOfIssue = inputWordCountOfIssue;
		}

		while (dataOfCurrentMonth >> inputNameOfPage >> inputWordCountOfPage >> inputNameOfIssue >> inputWordCountOfIssue)
		{
			i += 1;
			wordCountTable.push_back(empty);
			wordCountTable[i].wordCountTablePageName = inputNameOfPage;
			wordCountTable[i].wordCountTableWordCountOfPage = inputWordCountOfPage;
			wordCountTable[i].wordCountTableIssueName = inputNameOfIssue;
			wordCountTable[i].wordCountTableFullWordCountOfIssue = inputWordCountOfIssue;
		}

		while (Data2 >> inputNameOfPage >> inputWordCountOfPage >> inputNameOfIssue >> inputWordCountOfIssue)
		{
			i += 1;
			wordCountTable.push_back(empty);
			wordCountTable[i].wordCountTablePageName = inputNameOfPage;
			wordCountTable[i].wordCountTableWordCountOfPage = inputWordCountOfPage;
			wordCountTable[i].wordCountTableIssueName = inputNameOfIssue;
			wordCountTable[i].wordCountTableFullWordCountOfIssue = inputWordCountOfIssue;
		}

	}
	void makeNormalisedTitleTable(std::string inputFileStructureLocation)
	{
		std::ifstream data(inputFileStructureLocation + "\\inputs\\NormalisedTitlesns.tsv");
		std::string title = "";
		std::string normalisedTitle = "";
		normalisedTitleReference empty;
		int i = -1;

		while (data >> title >> normalisedTitle)
		{
			i += 1;
			normalisedTitlesTable.push_back(empty);
			normalisedTitlesTable[i].title = title;
			normalisedTitlesTable[i].normalisedTitle = normalisedTitle;
		}
	}
	
	// transformer
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
					copyfindTable[i].issueNameofLeftPage = copyfindTable[i].nameOfLeftPage.substr(0, 11) + copyfindTable[i].titleOfLeftPage;
					copyfindTable[i].copyfindFullWordCountOfLeftIssue = wordCountTable[t].wordCountTableFullWordCountOfIssue; // add issue wordcount
					newT = t;
					t = size(wordCountTable) - 1;
				}
			}
		}
	}
	void regexCopyfindTableTitles()
	{
		for (int i = 0; i < copyfindTable.size(); i++)
		{
			std::regex t("([A-Za-z-,'&]+)_[A-Z_0-9]+.txt");
			std::regex p("[A-Za-z-,'&]+_([A-Z_0-9]+).txt");
			std::regex u("([0-9]{4}.[0-9]{2}.[0-9]{2}_[A-Za-z-,'&]+_[A-Z_0-9]+).txt");
			std::string normallefttitle = "";
			std::string templefttitle = "";
			std::string normalrighttitle = "";
			std::string temprighttitle = "";

			copyfindTable[i].yearOfLeftPage = stoi(copyfindTable[i].copyfindPathOfLeftFile.substr(23, 4));
			copyfindTable[i].monthOfLeftPage = stoi(copyfindTable[i].copyfindPathOfLeftFile.substr(28, 2));
			copyfindTable[i].dayOfLeftPage = stoi(copyfindTable[i].copyfindPathOfLeftFile.substr(31, 2));
			templefttitle = std::regex_replace(copyfindTable[i].copyfindPathOfLeftFile.substr(34), t, "$1");
			for (int j = 0; j < size(normalisedTitlesTable); j++)
			{
				if (templefttitle == normalisedTitlesTable[j].title)
				{
					normallefttitle = normalisedTitlesTable[j].normalisedTitle;
				}
			}
			copyfindTable[i].titleOfLeftPage = normallefttitle;
			copyfindTable[i].pageNumberOfLeftPage = std::regex_replace(copyfindTable[i].copyfindPathOfLeftFile.substr(34), p, "$1");
			copyfindTable[i].normalisedNameOfLeftPage = copyfindTable[i].copyfindPathOfLeftFile.substr(23, 4) + "." + copyfindTable[i].copyfindPathOfLeftFile.substr(28, 2) + "." + copyfindTable[i].copyfindPathOfLeftFile.substr(31, 2) + "_" + normallefttitle + "_" + std::regex_replace(copyfindTable[i].copyfindPathOfLeftFile.substr(34), p, "$1");
			copyfindTable[i].nameOfLeftPage = std::regex_replace(copyfindTable[i].copyfindPathOfLeftFile.substr(23), u, "$1");
			copyfindTable[i].yearOfRightPage = stoi(copyfindTable[i].copyfindPathOfRightFile.substr(23, 4));
			copyfindTable[i].monthOfRightPage = stoi(copyfindTable[i].copyfindPathOfRightFile.substr(28, 2));
			copyfindTable[i].dayOfRightPage = stoi(copyfindTable[i].copyfindPathOfRightFile.substr(31, 2));
			temprighttitle = std::regex_replace(copyfindTable[i].copyfindPathOfRightFile.substr(34), t, "$1");
			for (int j = 0; j < size(normalisedTitlesTable); j++)
			{
				if (temprighttitle == normalisedTitlesTable[j].title)
				{
					normalrighttitle = normalisedTitlesTable[j].normalisedTitle;
				}
			}
			copyfindTable[i].titleOfRightPage = normalrighttitle;
			copyfindTable[i].pageOfRightPage = std::regex_replace(copyfindTable[i].copyfindPathOfRightFile.substr(34), p, "$1");
			copyfindTable[i].normalisedNameOfRightPage = copyfindTable[i].copyfindPathOfRightFile.substr(23, 4) + "." + copyfindTable[i].copyfindPathOfRightFile.substr(28, 2) + "." + copyfindTable[i].copyfindPathOfRightFile.substr(31, 2) + "_" + normalrighttitle + "_" + std::regex_replace(copyfindTable[i].copyfindPathOfRightFile.substr(34), p, "$1");
			copyfindTable[i].nameOfRightPage = std::regex_replace(copyfindTable[i].copyfindPathOfRightFile.substr(23), u, "$1");
		}
	}
	
};