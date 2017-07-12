#pragma once
#include "coresettings.h"

class inputter
{
public:

	//Variables
	double divisor;

	// Structs
	
	struct copyfindEntry {
		int copyfindPerfectMatch; // pull from copyfind file
		int copyfindLefthandMatch; // pull from copyfind file
		int copyfindRighthandMatch; // pull from copyfind file
		int copyfindAverageMatch; // process in makeCFTable
		int copyfindMaximumWordCount{ 0 }; // process in processMaximumValues
		double fullPageWordCountOfLeftPage{ 0 }; // pull from wordCountTable
		std::string issueNameofLeftPage{ }; // pull from wordCountTable
		int copyfindCombinedAverageWordCountForLeftIssue{ 0 }; // process in processMaximumValues
		double copyfindFullWordCountOfLeftIssue{ 0 }; // pull from BL table
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
		double maximumAverageWordCountForReprintsOnLaterPage{ 0 }; // (reprints) maximum average word count of target page; pull from cftable
		double fullWordCountofLaterPage{ 0 }; // (whole) full-page word count of target page; pull from cftable via wordCountTable
		std::string nameOfIssue{}; // issue of target article; pull from cftable
		double combinedAverageWordCountForIssue{ 0 }; // (reprints) maximum average word count of target issue; pull from cftable
		double fullWordCountOfIssue{ 0 }; // (whole) full-issue word count of targe page; pull from cftable 
		double percentageOfReprintedMaterialOnPage{ 0 }; // maximum average word count-to-page ratio; process in results
		double percentageOfReprintedMaterialInIssue{ 0 }; // all maximum average word counts-to-issue ratio; process in results
	};

	// Struct instances
	variableList processVariables;
	comparisonEntry emptyComparison;
	uniquePageEntry emptyPage;

	// Vectors
	std::vector<comparisonEntry> comparisonsTable;
	std::vector<uniquePageEntry> uniquePagesTable;
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
		std::string previousMonthFile = inputFileStructureLocation + "\\inputs\\rawmatchingreports\\" + processVariables.stringOfPreviousYear + "_" + processVariables.stringOfPreviousMonth + ".txt";
		std::string monthFile = inputFileStructureLocation + "\\inputs\\rawmatchingreports\\" + processVariables.stringOfYear + "_" + processVariables.stringOfMonth + ".txt";
		std::ifstream dataForPreviousMonth(previousMonthFile);
		std::ifstream dataForCurrentMonth(monthFile);
		int i = -1;

		while (dataForPreviousMonth >> inputPerfectMatch >> inputLeftMatch >> inputRightMatch >> inputPathOfLeftFile >> inputPathOfRightFile)
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
	void makeWordCountTable()
	{
		wordCountTableEntry empty;
		std::ifstream dataOfPreviousMonth(inputFileStructureLocation + "\\inputs\\wctables\\" + processVariables.stringOfSubsequentYear + "_" + processVariables.stringOfPreviousMonth + ".tsv");
		std::ifstream dataOfCurrentMonth(inputFileStructureLocation + "\\inputs\\wctables\\" + processVariables.stringOfYear + "_" + processVariables.stringOfMonth + ".tsv");
		std::ifstream Data2(inputFileStructureLocation + "\\inputs\\wctables\\" + processVariables.stringOfSubsequentYear + "_" + processVariables.stringOfSubsequentMonth + ".tsv");
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
	void makeNormalisedTitleTable()
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
	
	// comparisonsTable creator
	int findDaysBetweenWithDifferentYears(int i) // this is a sub-function of makeComparisonsTable
	{
		int A_Days = monthToDays(copyfindTable[i].monthOfLeftPage, isLeapYear(copyfindTable[i].yearOfLeftPage)) + copyfindTable[i].dayOfLeftPage;//calculate numbers days into target year 
		bool bIsLeapYear = isLeapYear(copyfindTable[i].yearOfRightPage); //determine if the source year is a leap year
		int B_Days = monthToDays(copyfindTable[i].monthOfRightPage, bIsLeapYear) + copyfindTable[i].dayOfRightPage; //calculate the number of days into source year

		if (bIsLeapYear) { B_Days = 366 - B_Days; } //calculate the number of days remaining in leap source year
		else { B_Days = 365 - B_Days; } //calculate the number of days remaining in non-leap source year

		return (A_Days + B_Days);
	}
	int findDaysBetweenWithSameYears(int i) // this is a sub-function of makeComparisonsTable
	{
		int A_Days = monthToDays(copyfindTable[i].monthOfLeftPage, isLeapYear(copyfindTable[i].yearOfLeftPage)) + copyfindTable[i].dayOfLeftPage; //calculate days in target year so far
		int B_Days = monthToDays(copyfindTable[i].monthOfRightPage, isLeapYear(copyfindTable[i].yearOfRightPage)) + copyfindTable[i].dayOfRightPage; //calculate days in source year so far
		return (A_Days - B_Days);
	}
	void transferCopyfindData(int i, size_t j) // this is a sub-function of makeComparisonsTable
	{
		comparisonsTable[j].perfectMatchOfComparison = copyfindTable[i].copyfindPerfectMatch; //perfect match
		comparisonsTable[j].leftHandMatchOfComparison = copyfindTable[i].copyfindLefthandMatch; //left match
		comparisonsTable[j].rightHandMatchOfComparison = copyfindTable[i].copyfindRighthandMatch; //right match
		comparisonsTable[j].laterPage.normalisedNameOfPage = copyfindTable[i].normalisedNameOfLeftPage; //normalised unique id for target
		comparisonsTable[j].laterPage.nameOfPage = copyfindTable[i].nameOfLeftPage; //unique id for target
		comparisonsTable[j].laterPage.titleOfPage = copyfindTable[i].titleOfLeftPage; //target title
		comparisonsTable[j].laterPage.yearOfPage = copyfindTable[i].yearOfLeftPage; //target year
		comparisonsTable[j].laterPage.monthOfPage = copyfindTable[i].monthOfLeftPage; //target month
		comparisonsTable[j].laterPage.dayOfPage = copyfindTable[i].dayOfLeftPage; //target day
		comparisonsTable[j].laterPage.pageNumberOfPage = copyfindTable[i].pageNumberOfLeftPage; //target page
		comparisonsTable[j].earlierPage.normalisedNameOfPage = copyfindTable[i].normalisedNameOfRightPage; //normalised unique id for source 
		comparisonsTable[j].earlierPage.nameOfPage = copyfindTable[i].nameOfRightPage; //unique id for source 
		comparisonsTable[j].earlierPage.titleOfPage = copyfindTable[i].titleOfRightPage; //source title
		comparisonsTable[j].earlierPage.yearOfPage = copyfindTable[i].yearOfRightPage; //source year
		comparisonsTable[j].earlierPage.monthOfPage = copyfindTable[i].monthOfRightPage; //source month
		comparisonsTable[j].earlierPage.dayOfPage = copyfindTable[i].dayOfRightPage; //source day
		comparisonsTable[j].earlierPage.pageNumberOfPage = copyfindTable[i].pageOfRightPage; //source page

	}
	void checkForUniqueLaterPage(int i) // this is a sub-function of makeComparisonsTable
	{
		std::string id = copyfindTable[i].normalisedNameOfLeftPage;
		auto pred = [id](const uniquePageEntry & item) {return item.nameOfLaterPage == id; };
		if (find_if(begin(uniquePagesTable), end(uniquePagesTable), pred) != end(uniquePagesTable))
		{
		}
		else
		{
			uniquePagesTable.push_back(emptyPage);
			uniquePagesTable[uniquePagesTable.size() - 1].nameOfLaterPage = copyfindTable[i].normalisedNameOfLeftPage;
		}
	}

	// transformer
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
	void makeComparisonsTable()

	{
		int maxDaysBetweenLaterAndEarlierPages = 21; //up to 1 year maximum, otherwise change the comparison logic
		int leftMatchTolerance = 90; //minimum left match
		int rightMatchTolerance = 90; //minimum right match
		int perfectMatchTolerance = 160; //minimum overall or perfect match

		for (int i = 0; i < size(copyfindTable); i++) //while data is available
		{
			if (copyfindTable[i].monthOfLeftPage != stoi(processVariables.stringOfMonth)
				&& 
				copyfindTable[i].monthOfRightPage != stoi(processVariables.stringOfMonth)) {}
			//do not include matches from same title
			else if (copyfindTable[i].titleOfLeftPage == copyfindTable[i].titleOfRightPage) {}

			//remove small matches
			else if (copyfindTable[i].copyfindRighthandMatch <= rightMatchTolerance && copyfindTable[i].copyfindLefthandMatch <= leftMatchTolerance && copyfindTable[i].copyfindRighthandMatch + copyfindTable[i].copyfindLefthandMatch <= perfectMatchTolerance) {}

			//if the later page's year is later than the earlier page's year
			else if (copyfindTable[i].yearOfLeftPage > copyfindTable[i].yearOfRightPage)
			{
				// and they are concurrent years
				if (copyfindTable[i].yearOfLeftPage - copyfindTable[i].yearOfRightPage == 1)
				{
					//if days between is fewer than the tolerance, proceed to print item in comparisons database
					if (findDaysBetweenWithDifferentYears(i) <= maxDaysBetweenLaterAndEarlierPages)
					{
						if (i == 0 || comparisonsTable.size() == 0)
						{
							comparisonsTable.push_back(emptyComparison);
							transferCopyfindData(i, 0);
							checkForUniqueLaterPage(i);
						}
						else if (copyfindTable[i].normalisedNameOfRightPage >= comparisonsTable[comparisonsTable.size() - 1].earlierPage.normalisedNameOfPage)
						{
							comparisonsTable.push_back(emptyComparison);
							transferCopyfindData(i, comparisonsTable.size() - 1);
							checkForUniqueLaterPage(i);
						}

						else
						{
							for (size_t j = 0; j < comparisonsTable.size() - 1; ++j)
							{
								if (copyfindTable[i].normalisedNameOfRightPage >= comparisonsTable[j].earlierPage.normalisedNameOfPage)
								{
									continue;
								}
								else
								{
									comparisonsTable.insert(comparisonsTable.begin() + j, emptyComparison);
									transferCopyfindData(i, j);
									checkForUniqueLaterPage(i);
									break;
								}
							}
						}
					}
				}
			}

			// if they are the same year and the target month is later than the source month, 
			else if (copyfindTable[i].monthOfLeftPage > copyfindTable[i].monthOfRightPage
				// or they are the same month and the target day is on or later than the source day
				|| copyfindTable[i].monthOfLeftPage == copyfindTable[i].monthOfRightPage
				&& copyfindTable[i].dayOfLeftPage >= copyfindTable[i].dayOfRightPage)
			{
				//calculate days between articles to see if equal or under Max Days; if so, proceed
				if (findDaysBetweenWithSameYears(i) <= maxDaysBetweenLaterAndEarlierPages)
					if (i == 0 || comparisonsTable.size() == 0)
					{
						comparisonsTable.push_back(emptyComparison);
						transferCopyfindData(i, 0);
						checkForUniqueLaterPage(i);
					}
					else if (copyfindTable[i].normalisedNameOfRightPage >= comparisonsTable[comparisonsTable.size() - 1].earlierPage.normalisedNameOfPage)
					{
						comparisonsTable.push_back(emptyComparison);
						transferCopyfindData(i, comparisonsTable.size() - 1);
						checkForUniqueLaterPage(i);
					}
					else
					{
						for (size_t j = 0; j < comparisonsTable.size() - 1; ++j)
						{
							if (copyfindTable[i].normalisedNameOfRightPage >= comparisonsTable[j].earlierPage.normalisedNameOfPage)
							{
								continue;
							}
							else
							{
								comparisonsTable.insert(comparisonsTable.begin() + j, emptyComparison);
								transferCopyfindData(i, j);
								checkForUniqueLaterPage(i);
								break;
							}
						}
					}
			}
		}

		sort(uniquePagesTable.begin(), uniquePagesTable.end(), [](const uniquePageEntry& lhs, const uniquePageEntry& rhs)
		{
			return lhs.nameOfLaterPage < rhs.nameOfLaterPage;
		});
	}
	void crossReferenceValuesInWordCountAndCopyfindTables() // combines British Library and Copyfind (average match wordcount) data
	{
		for (size_t i = 0; i < size(copyfindTable); ++i) // iterate through cftable
		{
			if (copyfindTable[i].monthOfLeftPage == std::stoi(processVariables.stringOfMonth))
			{
				for (size_t t = 0; t < size(wordCountTable); ++t)
				{
					if (copyfindTable[i].nameOfLeftPage == wordCountTable[t].wordCountTablePageName) // if the cfuid is the same as the bluid
					{
						copyfindTable[i].fullPageWordCountOfLeftPage = wordCountTable[t].wordCountTableWordCountOfPage; // add full wordcount
						copyfindTable[i].issueNameofLeftPage = copyfindTable[i].nameOfLeftPage.substr(0, 11) + copyfindTable[i].titleOfLeftPage;
						copyfindTable[i].copyfindFullWordCountOfLeftIssue = wordCountTable[t].wordCountTableFullWordCountOfIssue; // add issue wordcount
						break;
					}
				}
			}
		}
	}
	
};