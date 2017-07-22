#pragma once
#include "coresettings.h"

bool CompareRecords(const matchDataEntry& a, const matchDataEntry& b);

class writer
{
public:

//    _____                   _    __      __        _       _     _           
//   |_   _|                 | |   \ \    / /       (_)     | |   | |          
//     | |  _ __  _ __  _   _| |_   \ \  / /_ _ _ __ _  __ _| |__ | | ___  ___ 
//     | | | '_ \| '_ \| | | | __|   \ \/ / _` | '__| |/ _` | '_ \| |/ _ \/ __|
//    _| |_| | | | |_) | |_| | |_     \  / (_| | |  | | (_| | |_) | |  __/\__ \
//   |_____|_| |_| .__/ \__,_|\__|     \/ \__,_|_|  |_|\__,_|_.__/|_|\___||___/
//               | |                                                           
//               |_|                                                           

	variableList processVariables;

	// Tolerance variables
	int maxDaysBetweenPages = 21;
	int leftMatchTolerance = 90; //minimum left match
	int rightMatchTolerance = 90; //minimum right match
	int perfectMatchTolerance = 160; //minimum overall or perfect match

	// Import Data Variables
	int inputDataPerfectMatch;
	int inputDataLeftMatch;
	int inputDataRightMatch;
	std::string inputDataPathOfLeftFile;
	std::string inputDataPathOfRightFile;
	size_t leftPageHolder; // Index Holding Variable for left page, not "later" page
	size_t rightPageHolder; // Index Holding Variable for right page,  not "earlier" page

//     _____                  _____ _                   _       
//    / ____|                / ____| |                 | |      
//   | |     ___  _ __ ___  | (___ | |_ _ __ _   _  ___| |_ ___ 
//   | |    / _ \| '__/ _ \  \___ \| __| '__| | | |/ __| __/ __|
//   | |___| (_) | | |  __/  ____) | |_| |  | |_| | (__| |_\__ \
//    \_____\___/|_|  \___| |_____/ \__|_|   \__,_|\___|\__|___/
//                                                              

	// Page Struct (For Unique Page Entries Only; every instance shares this data)
	struct pageEntry // Contains Unique Page Metadata
	{
		std::string year; // Substr'd from inputPathOfLeftFile or inputPathOfRightFile
		std::string month;  // Substr'd from inputPathOfLeftFile or inputPathOfRightFile
		std::string day;  // Substr'd from inputPathOfLeftFile or inputPathOfRightFile
		std::string title;  // Substr'd from inputPathOfLeftFile or inputPathOfRightFile
		std::string pageNumber;  // Substr'd from inputPathOfLeftFile or inputPathOfRightFile
		int dateEnumeration; // A single number representing date in relation to 14 September 1752 (British move to Gregorian Calendar)
		std::string uniquePageID; // The filename minus system path data
		std::string uniqueIssueID; // The unique page ID minus the page number data
		size_t issueIndex; // Cross reference to Unique Issue IDs vector
		double maximumAverageWordCountofPage; // Computed by calculateMaximumIssueWordCount()
		double maximumAverageWordCountofIssue; // Computed by calculateMaximumIssueWordCount()
		int bestDirectLinkofPage{ -1 }; // Which earlier page has best perfect match / date score
		bool bDirectedLinkMonth{ false }; // Is its best match in the right date range
		double fullWordCountOfPage; // Pulled directly from WordCount Manifest
		double fullWordCountOfIssue; // Pulled directly from WordCount Manifest
		double percentageOfPage; // Computed by calculateMaximumIssueWordCount()
		double percenageOfIssue; // Computed by calculateMaximumIssueWordCount()
	};

	// Unique Page ID Vector; a simple list of known page IDs
	std::vector <std::string> uniquePageIDs;

	// Unique Issue ID Vector; a simple list of known issue IDs
	std::vector <std::string> uniqueIssueIDs;

	// Instance of Page Struct
	pageEntry emptyPage{};

	// Vector of Unique Page Entries
	std::vector <pageEntry> uniquePageEntries;

//    _____        _         _    _ _   _ _ _ _   _           
//   |  __ \      | |       | |  | | | (_) (_) | (_)          
//   | |  | | __ _| |_ ___  | |  | | |_ _| |_| |_ _  ___  ___ 
//   | |  | |/ _` | __/ _ \ | |  | | __| | | | __| |/ _ \/ __|
//   | |__| | (_| | ||  __/ | |__| | |_| | | | |_| |  __/\__ \
//   |_____/ \__,_|\__\___|  \____/ \__|_|_|_|\__|_|\___||___/
//                                                            
//                                                            

	int enumeratedYears;
	int enumeratedMonths;

	bool isLeapYear(int year) //determine if the year is a leap year
	{
		// Only valid on or after Thursday, September 14, 1752
		if (year % 4 != 0)
			return false;
		else if (year % 100 != 0)
			return true;
		else if (year % 400 != 0)
			return false;
		else
			return true;
	}

	int enumerateMonths(int month, bool isLeapYear) //convert days, months and years into day of that year
	{
		// Only valid on or after Thursday, September 14, 1752
		if (!isLeapYear) //if it is not a leap year
		{
			switch (month)
			{
			case 1: return 0;
			case 2: return 31;
			case 3: return 59;
			case 4: return 90;
			case 5: return 120;
			case 6: return 151;
			case 7: return 181;
			case 8: return 212;
			case 9: return 243;
			case 10: return 273;
			case 11: return 304;
			case 12: return 334;
			default: return 0;
			}
		}
		else // if it is a leap year
		{
			switch (month)
			{
			case 1: return 0;
			case 2: return 31;
			case 3: return 60;
			case 4: return 91;
			case 5: return 121;
			case 6: return 152;
			case 7: return 182;
			case 8: return 213;
			case 9: return 244;
			case 10: return 274;
			case 11: return 305;
			case 12: return 335;
			default: return 0;
			}
		}
	}

	// Calculate date enumeration 
	int enumerateYears(int inputYear)
	{
		int numberOfYears = inputYear - 1753;
		if (inputYear == 1752)
		{
			inputYear -= 1753;
			return 0;
		}
		else if (inputYear < 1800)
		{
			enumeratedYears = 109 + 365 * numberOfYears + numberOfYears / 4;
			return enumeratedYears;
		}
		else if (inputYear < 1900)
		{
			enumeratedYears = 109 + 365 * numberOfYears + numberOfYears / 4 + 1;
			return enumeratedYears;
		}
		else
		{
			enumeratedYears = 109 + 365 * numberOfYears + numberOfYears / 4 + 2;
			return enumeratedYears;
		}
	}

	int enumerateDate(int year, int month, int day)
	{
		// Use enumerate functions to create dateEnumeration
		int dateEnumeration = enumerateYears(year) + enumerateMonths(month, isLeapYear(year)) + day;
		return dateEnumeration;
	}


//   __          __           _    _____                  _       
//   \ \        / /          | |  / ____|                | |      
//    \ \  /\  / /__  _ __ __| | | |     ___  _   _ _ __ | |_ ___ 
//     \ \/  \/ / _ \| '__/ _` | | |    / _ \| | | | '_ \| __/ __|
//      \  /\  / (_) | | | (_| | | |___| (_) | |_| | | | | |_\__ \
//       \/  \/ \___/|_|  \__,_|  \_____\___/ \__,_|_| |_|\__|___/
//                                                                

	// Wordcount Manifest Import Holding Variables
	std::string wordCountInputDataUniquePageID; // The filename minus system path data
	double wordCountInputDataFullWordCountOfPage; // Pulled directly from WordCount Manifest
	std::string wordCountInputDataUniqueIssueID; // The unique page ID minus the page number data
	double wordCountInputDataFullWordCountOfIssue; // Pulled directly from WordCount Manifest

	// Maximum Average WordCount Holding Variables
	double sumOfPagesInIssue{ 0 };

	// Wordcount Vector Entry
	struct fullWordCountEntry
	{
		double inputtedfullPageWordCount;
		double inputtedfullIssueWordCount;
	};

	// Instance of Wordcount Vector Entry
	fullWordCountEntry emptyWordCountEntry{};

	// Wordcount Vector
	std::vector <fullWordCountEntry> fullWordCountEntries;

	// Wordcount Unique Page ID List
	std::vector <std::string> fullWordCountEntries_UniquePageIDs;

	// Average Word Counts of Issue Struct
	struct averageWordCountofIssue // Contains all the maximumAverageWordCountofPage in an issue, to calculate maximumAverageWordCountofIssue
	{
		std::vector<size_t> pagesInIssue; // lists all pages in issue that have a wordcount associated with them
		std::vector<double> maximumWordCounts; // push_back every time a new maximumAverageWordCountofPage is calculated
	};

	// Instance of Average Word Count of Issue Struct
	averageWordCountofIssue emptyAverageWordCountofIssue{};

	// Vector of Average Word Counts of Issue Entries
	std::vector <averageWordCountofIssue> averageWordCountofIssueList;

	// Import WordCount data
	void importWordCountData()
	{
		// Set input files	
		processVariables.stringOfPreviousYear + "_" + processVariables.stringOfPreviousMonth + ".tsv";
		std::ifstream dataForPreviousMonth(inputFileStructureLocation + "\\inputs\\" + "wctables\\" + processVariables.stringOfPreviousYear + "_" + processVariables.stringOfPreviousMonth + ".tsv");
		std::ifstream dataForCurrentMonth(inputFileStructureLocation + "\\inputs\\" + "wctables\\" + processVariables.stringOfYear + "_" + processVariables.stringOfMonth + ".tsv");
		std::ifstream dataForSubsequentMonth(inputFileStructureLocation + "\\inputs\\" + "wctables\\" + processVariables.stringOfSubsequentYear + "_" + processVariables.stringOfSubsequentMonth + ".tsv");

		while (dataForPreviousMonth >> wordCountInputDataUniquePageID >> wordCountInputDataFullWordCountOfPage >> wordCountInputDataUniqueIssueID >> wordCountInputDataFullWordCountOfIssue)
		{
			// Push back word count vector
			fullWordCountEntries.push_back(emptyWordCountEntry);
			size_t current = fullWordCountEntries.size() - 1;

			// Put line of file data into current Word Count struct
			fullWordCountEntries[current].inputtedfullPageWordCount = wordCountInputDataFullWordCountOfPage;
			fullWordCountEntries[current].inputtedfullIssueWordCount = wordCountInputDataFullWordCountOfIssue;

			// Push back word count unique pages vector
			fullWordCountEntries_UniquePageIDs.push_back("");
			fullWordCountEntries_UniquePageIDs[fullWordCountEntries_UniquePageIDs.size() - 1] = wordCountInputDataUniquePageID;
		}

		while (dataForCurrentMonth >> wordCountInputDataUniquePageID >> wordCountInputDataFullWordCountOfPage >> wordCountInputDataUniqueIssueID >> wordCountInputDataFullWordCountOfIssue)
		{
			// Push back word count vector
			fullWordCountEntries.push_back(emptyWordCountEntry);
			size_t current = fullWordCountEntries.size() - 1;

			// Put line of file data into current Word Count struct
			fullWordCountEntries[current].inputtedfullPageWordCount = wordCountInputDataFullWordCountOfPage;
			fullWordCountEntries[current].inputtedfullIssueWordCount = wordCountInputDataFullWordCountOfIssue;

			// Push back word count unique pages vector
			fullWordCountEntries_UniquePageIDs.push_back("");
			fullWordCountEntries_UniquePageIDs[fullWordCountEntries_UniquePageIDs.size() - 1] = wordCountInputDataUniquePageID;
		}

		while (dataForSubsequentMonth >> wordCountInputDataUniquePageID >> wordCountInputDataFullWordCountOfPage >> wordCountInputDataUniqueIssueID >> wordCountInputDataFullWordCountOfIssue)
		{
			// Push back word count vector
			fullWordCountEntries.push_back(emptyWordCountEntry);
			size_t current = fullWordCountEntries.size() - 1;

			// Put line of file data into current Word Count struct
			fullWordCountEntries[current].inputtedfullPageWordCount = wordCountInputDataFullWordCountOfPage;
			fullWordCountEntries[current].inputtedfullIssueWordCount = wordCountInputDataFullWordCountOfIssue;

			// Push back word count unique pages vector
			fullWordCountEntries_UniquePageIDs.push_back("");
			fullWordCountEntries_UniquePageIDs[fullWordCountEntries_UniquePageIDs.size() - 1] = wordCountInputDataUniquePageID;
		}
	}

	// Import Wordcount metadata based on unique page id
	void transferFullWordCountEntry(size_t current)
	{
		std::string testUniqueId = uniquePageIDs[current];

		// If uniquePageID exists in Word Counts vector,
		if (find(fullWordCountEntries_UniquePageIDs.begin(), fullWordCountEntries_UniquePageIDs.end(), testUniqueId) != fullWordCountEntries_UniquePageIDs.end())
		{
			// Find the page's location
			std::vector<std::string>::iterator it = find(fullWordCountEntries_UniquePageIDs.begin(), fullWordCountEntries_UniquePageIDs.end(), testUniqueId);
			// Put id in placeholder variable leftPageHolder (in Copyfind Holder Variables)
			int indexNumber = int(it - fullWordCountEntries_UniquePageIDs.begin());

			// Push wordcount values
			uniquePageEntries[current].fullWordCountOfPage = fullWordCountEntries[indexNumber].inputtedfullPageWordCount;
			uniquePageEntries[current].fullWordCountOfIssue = fullWordCountEntries[indexNumber].inputtedfullIssueWordCount;
		}
	}

	// Create Issue Reference List
	void crossReferenceWithAverageWordCountOfIssueEntry(size_t current, bool bNew)
	{
		if (bNew)
		{
			// Push back unique issue IDs vector
			uniqueIssueIDs.push_back(uniquePageEntries[current].uniqueIssueID);

			// Push back issue word count vector
			averageWordCountofIssueList.push_back(emptyAverageWordCountofIssue);

			// Put Issue ID in unique pages list
			uniquePageEntries[current].issueIndex = uniqueIssueIDs.size() - 1;
		}

		else
		{
			// Put Issue ID in unique pages list
			uniquePageEntries[current].issueIndex = size_t(find(uniqueIssueIDs.begin(), uniqueIssueIDs.end(), uniquePageEntries[current].uniqueIssueID) - uniqueIssueIDs.begin());
		}

		// Push index number of unique page to pagesInIssue vector
		averageWordCountofIssueList[uniquePageEntries[current].issueIndex].pagesInIssue.push_back(current);

	}

	// Calculate Maximum Word Count per Issue
	void calculateMaximumIssueWordCount()
	{
		// Go through every issue
		for (size_t i = 0; i < averageWordCountofIssueList.size(); i++)
		{
			// Go through each page in the issue page list (<16) 
			for (size_t j = 0; j < averageWordCountofIssueList[i].pagesInIssue.size(); j++)
			{
				// Use the page index to retrieve the maximum value and add it to a sum
				sumOfPagesInIssue += uniquePageEntries[averageWordCountofIssueList[i].pagesInIssue[j]].maximumAverageWordCountofPage;
			}

			// Once you have a full sum, go back through the pages again
			// Go through each page in the issue page list (<16) 
			for (size_t j = 0; j < averageWordCountofIssueList[i].pagesInIssue.size(); j++)
			{
				// Use the page index to set the issue Maximum Word Count
				uniquePageEntries[averageWordCountofIssueList[i].pagesInIssue[j]].maximumAverageWordCountofIssue = sumOfPagesInIssue;
				uniquePageEntries[averageWordCountofIssueList[i].pagesInIssue[j]].percenageOfIssue = uniquePageEntries[averageWordCountofIssueList[i].pagesInIssue[j]].maximumAverageWordCountofIssue / uniquePageEntries[i].fullWordCountOfIssue;
			}
			sumOfPagesInIssue = 0;
		}
	}

//    __  __       _       _               
//   |  \/  |     | |     | |              
//   | \  / | __ _| |_ ___| |__   ___  ___ 
//   | |\/| |/ _` | __/ __| '_ \ / _ \/ __|
//   | |  | | (_| | || (__| | | |  __/\__ \
//   |_|  |_|\__,_|\__\___|_| |_|\___||___/
//                                                                                                                                 
	// Instance of Match Struct
	matchDataEntry emptyMatch{};
	// Vector of Match Data Entries
	std::vector <matchDataEntry> matchDataEntries;

	// Create Match Data Entries for Match Data Entry Vector
	void createMatchDataEntry()
	{
		// Create match entry
		matchDataEntries.push_back(emptyMatch);
		size_t currentMatchEntry = matchDataEntries.size() - 1;
		matchDataEntries[currentMatchEntry].copyfindPerfectMatch = inputDataPerfectMatch;

		// Create average (copyfindAverageMatch) based on both inputRightWordCount and inputLeftWordCount
		matchDataEntries[currentMatchEntry].copyfindAverageMatch = (inputDataLeftMatch + inputDataRightMatch) / 2;

		// Compare dateEnumerations to place in correct order in match entry
		if (uniquePageEntries[leftPageHolder].dateEnumeration < uniquePageEntries[rightPageHolder].dateEnumeration)
		{
			// Input leftPageHolder into earlierPageEntryIndexNumber
			matchDataEntries[currentMatchEntry].earlierPageEntryIndexNumber = leftPageHolder;

			// Input inputLeftWordCount into copyfindEarlierMatchWordCount
			matchDataEntries[currentMatchEntry].copyfindEarlierMatchWordCount = inputDataLeftMatch;

			// Input rightPageHolder into laterPageEntryIndexNumber
			matchDataEntries[currentMatchEntry].laterPageEntryIndexNumber = rightPageHolder;

			// Input inputrightWordCount into copyfindLaterMatchWordCount
			matchDataEntries[currentMatchEntry].copyfindLaterPageMatchWordCount = inputDataRightMatch;

		}

		// If uniquePageList[rightPageHolder].dateEnumeration < uniquePageList[lefttPageHolder].dateEnumeration
		else
		{
			// Input rightPageHolder into earlierPageEntryIndexNumber
			matchDataEntries[currentMatchEntry].earlierPageEntryIndexNumber = rightPageHolder;

			// Input inputRightWordCount into copyfindEarlierMatchWordCount
			matchDataEntries[currentMatchEntry].copyfindEarlierMatchWordCount = inputDataRightMatch;

			// Input leftPageHolder into laterPageEntryIndexNumber
			matchDataEntries[currentMatchEntry].laterPageEntryIndexNumber = leftPageHolder;

			// Input inputLeftWordCount into copyfindLaterMatchWordCount
			matchDataEntries[currentMatchEntry].copyfindLaterPageMatchWordCount = inputDataLeftMatch;
		}

		// Add Average Word Count to Page List
		// If the average match of the existing Maximum Average Word Count is less than the current perfect match
		if (uniquePageEntries[leftPageHolder].maximumAverageWordCountofPage < matchDataEntries[currentMatchEntry].copyfindAverageMatch)
		{
			// update the maximum average wordcount data
			uniquePageEntries[leftPageHolder].maximumAverageWordCountofPage = matchDataEntries[currentMatchEntry].copyfindAverageMatch;

			// update the page percentage
			uniquePageEntries[leftPageHolder].percentageOfPage = uniquePageEntries[leftPageHolder].maximumAverageWordCountofPage / uniquePageEntries[leftPageHolder].fullWordCountOfPage;
		}

//     _____            _   _             
//    / ____|          | | (_)            
//   | (___   ___  _ __| |_ _ _ __   __ _ 
//    \___ \ / _ \| '__| __| | '_ \ / _` |
//    ____) | (_) | |  | |_| | | | | (_| |
//   |_____/ \___/|_|   \__|_|_| |_|\__, |
//                                   __/ |
//                                  |___/ 

		// Set Sorting Variables
		matchDataEntries[currentMatchEntry].earlierEnumeratedDate = uniquePageEntries[matchDataEntries[currentMatchEntry].earlierPageEntryIndexNumber].dateEnumeration;

		matchDataEntries[currentMatchEntry].daysBetween =
			uniquePageEntries[matchDataEntries[currentMatchEntry].laterPageEntryIndexNumber].dateEnumeration - matchDataEntries[currentMatchEntry].earlierEnumeratedDate;

		matchDataEntries[currentMatchEntry].earlierTitle = uniquePageEntries[matchDataEntries[currentMatchEntry].earlierPageEntryIndexNumber].title;

		matchDataEntries[currentMatchEntry].earlierPageNumber = uniquePageEntries[matchDataEntries[currentMatchEntry].earlierPageEntryIndexNumber].pageNumber;

		// Does it meet basic date requirements for a meme
		if (matchDataEntries[currentMatchEntry].daysBetween < maxDaysBetweenPages
			&&
			uniquePageEntries[rightPageHolder].month == processVariables.stringOfMonth)
		{
			matchDataEntries[currentMatchEntry].bMeme = true;
		}

		// Does it meet basic date requirements for a direct link
		if (matchDataEntries[currentMatchEntry].daysBetween < maxDaysBetweenPages
			&&
			uniquePageEntries[leftPageHolder].month == processVariables.stringOfMonth
			&&
			matchDataEntries[currentMatchEntry].daysBetween != 0)
		{
			// If this is the first time you've assigned a Best Direct Link, assign it
			if (uniquePageEntries[leftPageHolder].bestDirectLinkofPage == -1)
			{
				uniquePageEntries[leftPageHolder].bestDirectLinkofPage = int(matchDataEntries[currentMatchEntry].earlierPageEntryIndexNumber);
			}

			// If the perfect match of the existing Best Direct Link is less than the current perfect match
			else if (matchDataEntries[uniquePageEntries[leftPageHolder].bestDirectLinkofPage].copyfindPerfectMatch < inputDataPerfectMatch)
			{
				// update the best link data
				uniquePageEntries[leftPageHolder].bestDirectLinkofPage = int(matchDataEntries[currentMatchEntry].earlierPageEntryIndexNumber);
			}
			// If the perfect match of the existing Best Direct Link is equal to the current perfect match
			else if (matchDataEntries[uniquePageEntries[leftPageHolder].bestDirectLinkofPage].copyfindPerfectMatch == int(inputDataPerfectMatch))
			{
				// but the existing date is later than the current earlier page date
				if (matchDataEntries[uniquePageEntries[leftPageHolder].bestDirectLinkofPage].earlierEnumeratedDate > matchDataEntries[currentMatchEntry].earlierEnumeratedDate)
				{
					// update the best link data
					uniquePageEntries[leftPageHolder].bestDirectLinkofPage = int(matchDataEntries[currentMatchEntry].earlierPageEntryIndexNumber);
				}
			}
		}

		// Does it meet date requirements for an evolutionary dead end
		if (matchDataEntries[currentMatchEntry].daysBetween < maxDaysBetweenPages
			&&
			(uniquePageEntries[rightPageHolder].month == processVariables.stringOfMonth)
			|| uniquePageEntries[leftPageHolder].month == processVariables.stringOfMonth)
		{
			uniquePageEntries[leftPageHolder].bDirectedLinkMonth = true;
		}
	}

//     _____                   __ _           _ 
//    / ____|                 / _(_)         | |
//   | |     ___  _ __  _   _| |_ _ _ __   __| |
//   | |    / _ \| '_ \| | | |  _| | '_ \ / _` |
//   | |___| (_) | |_) | |_| | | | | | | | (_| |
//    \_____\___/| .__/ \__, |_| |_|_| |_|\__,_|
//               | |     __/ |                  
//               |_|    |___/                                                        

// Create Unique Page Entries for Unique Pages Vector
	void createUniquePageEntry(bool bLeft)
	{
		// Create page entry in unique pages array
		uniquePageEntries.push_back(emptyPage);
		size_t current = uniquePageEntries.size() - 1;
		std::string holderPath; // holds the relevant path for processing

		if (bLeft)
		{
			holderPath = inputDataPathOfLeftFile;
		}
		else
		{
			holderPath = inputDataPathOfRightFile;
		}

		// Fill in unique page id
		uniquePageEntries[current].uniquePageID = holderPath.substr(23, holderPath.size() - 27);

		// Fill in unique issue id
		uniquePageEntries[current].uniqueIssueID = holderPath.substr(23, holderPath.size() - 32);

		// Substring basic normalised metadata fields
		uniquePageEntries[current].year = holderPath.substr(23, 4);
		uniquePageEntries[current].month = holderPath.substr(28, 2);
		uniquePageEntries[current].day = holderPath.substr(31, 2);
		uniquePageEntries[current].title = holderPath.substr(34, holderPath.size() - 43);
		uniquePageEntries[current].pageNumber = holderPath.substr(holderPath.size() - 8, 4);

		// Push unique page ID to unique page id vector
		uniquePageIDs.push_back(uniquePageEntries[current].uniquePageID);

		// Use enumerate functions to create dateEnumeration
		uniquePageEntries[current].dateEnumeration = enumerateDate(std::stoi(uniquePageEntries[current].year), std::stoi(uniquePageEntries[current].month), std::stoi(uniquePageEntries[current].day));

		// Transfer full word count data from imported table to unique pages list
		transferFullWordCountEntry(current);

		if (uniqueIssueIDs.size() == 0)
		{
			// Add and cross reference page, issue, and average word counts data
			crossReferenceWithAverageWordCountOfIssueEntry(current, true);
		}

		// If unqiueIssueID exists in uniqueIssueIDs vector,
		else if (find(uniqueIssueIDs.begin(), uniqueIssueIDs.end(), uniquePageEntries[current].uniqueIssueID) != uniqueIssueIDs.end())
		{
			// Cross reference page, issue, and average word counts data
			crossReferenceWithAverageWordCountOfIssueEntry(current, false);
		}

		// If the uniqueIssueID doesn't exist in the uniqueIssueIDs vector
		else
		{
			// Add and cross reference page, issue, and average word counts data
			crossReferenceWithAverageWordCountOfIssueEntry(current, true);
		}

		// Push the unique page list index number to the page holder
		if (bLeft)
		{
			leftPageHolder = uniquePageEntries.size() - 1;
		}
		else
		{
			rightPageHolder = uniquePageEntries.size() - 1;
		}
	}

	void processCopyfindData()
	{
		// If the new match tolerance isn't met, ignore line
		if (inputDataPerfectMatch<perfectMatchTolerance && inputDataRightMatch<rightMatchTolerance 			&& inputDataLeftMatch<leftMatchTolerance) {}

		// If either substring month is beyond settable scope (+/- 1 month default), ignore line
		else if (inputDataPathOfLeftFile.substr(28, 2) != processVariables.stringOfPreviousMonth
			&& inputDataPathOfLeftFile.substr(28, 2) != processVariables.stringOfMonth
			&& inputDataPathOfRightFile.substr(28, 2) != processVariables.stringOfPreviousMonth
			&& inputDataPathOfRightFile.substr(28, 2) != processVariables.stringOfMonth) {
		}

		// If the title is the same for both sides, ignore line
		else if (inputDataPathOfLeftFile.substr(34, inputDataPathOfLeftFile.size() - 43) == inputDataPathOfRightFile.substr(34, inputDataPathOfRightFile.size() - 43)) {}

		// If at least one month is in scope
		else
		{
			// If this is the first entry
			if (uniquePageEntries.size() == 0)
			{
				// Create the first entry (left)
				createUniquePageEntry(true);

				// Create the second entry (right)
				createUniquePageEntry(false);

				// Create match data
				createMatchDataEntry();
			}

			// If it isn't the first entry
			else
			{
				// If Lefthand Path exists in uniquePageIDs vector,
				if (find(uniquePageIDs.begin(), uniquePageIDs.end(), inputDataPathOfLeftFile.substr(23, inputDataPathOfLeftFile.size() - 27)) != uniquePageIDs.end())
				{
					// Put id in placeholder variable leftPageHolder
					leftPageHolder = int(find(uniquePageIDs.begin(), uniquePageIDs.end(), inputDataPathOfLeftFile.substr(23, inputDataPathOfLeftFile.size() - 27)) - uniquePageIDs.begin());
				}

				// If not the uniquePageID doesn't exist in the uniquePageIDs vector
				else
				{
					// Create the left entry
					createUniquePageEntry(true);
				}

				// If Righthand Path exists in uniquePage vector, 
				if (find(uniquePageIDs.begin(), uniquePageIDs.end(), inputDataPathOfRightFile.substr(23, inputDataPathOfRightFile.size() - 27)) != uniquePageIDs.end())
				{
					// Put id in placeholder variable leftPageHolder 
					rightPageHolder = int(find(uniquePageIDs.begin(), uniquePageIDs.end(), inputDataPathOfRightFile.substr(23, inputDataPathOfRightFile.size() - 27)) - uniquePageIDs.begin());
				}

				// If not 
				else
				{
					// Create the right entry 
					createUniquePageEntry(false);
				}

				// Create match data
				createMatchDataEntry();
			}
		}
	}

	// Import Copyfind data; main function of this header
	void importCopyfindData()
	{
		// Set input files	
		std::ifstream dataForPreviousMonth(inputFileStructureLocation + "\\inputs\\" + "rawmatchingreports\\" + processVariables.stringOfPreviousYear + "_" + processVariables.stringOfPreviousMonth + ".tsv");
		std::ifstream dataForCurrentMonth(inputFileStructureLocation + "\\inputs\\" + "rawmatchingreports\\" + processVariables.stringOfYear + "_" + processVariables.stringOfMonth + ".tsv");

		while (dataForPreviousMonth >> inputDataPerfectMatch >> inputDataLeftMatch >> inputDataRightMatch >> inputDataPathOfLeftFile >> inputDataPathOfRightFile)
		{
			processCopyfindData();
		}

		while (dataForCurrentMonth >> inputDataPerfectMatch >> inputDataLeftMatch >> inputDataRightMatch >> inputDataPathOfLeftFile >> inputDataPathOfRightFile)
		{
			processCopyfindData();
		}
	}

//    _____                       
//   |  __ \                      
//   | |__) |___  __ _  _____  __ 
//   |  _  // _ \/ _` |/ _ \ \/ / 
//   | | \ |  __| (_| |  __/>  <  
//   |_|  \_\___|\__, |\___/_/\_\ 
//                __/ |                                                        
//               |___/           

	struct normalisedTitleReference {
		std::string title; // BL title
		std::string normalisedTitle; // Normalised title
	};

	std::vector<normalisedTitleReference> normalisedTitlesTable;

	void makeNormalisedTitleTable()
	{
		std::ifstream data(inputFileStructureLocation + "\\inputs\\" + "NormalisedTitlesns.tsv");
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

	// Normalise Titles
	void regexUniquePageEntriesTitles()
	{
		for (size_t i = 0; i < uniquePageEntries.size(); i++)
		{
			for (size_t j = 0; j < size(normalisedTitlesTable); j++)
			{
				if (uniquePageEntries[i].title == normalisedTitlesTable[j].title)
				{
					uniquePageEntries[i].title = normalisedTitlesTable[j].normalisedTitle;
				}
			}
		}
	}

//     ____        _               _       
//    / __ \      | |             | |      
//   | |  | |_   _| |_ _ __  _   _| |_ ___ 
//   | |  | | | | | __| '_ \| | | | __/ __|
//   | |__| | |_| | |_| |_) | |_| | |_\__ \
//    \____/ \__,_|\__| .__/ \__,_|\__|___/
//                    | |                  
//                    |_|                  

	void writeOutputs()
	{
		std::sort(matchDataEntries.begin(), matchDataEntries.end(), &CompareRecords);

		// Meme List
		std::ofstream memeData(inputFileStructureLocation + "\\outputs\\" + "memes\\" + processVariables.stringOfYear + "_" + processVariables.stringOfMonth + ".tsv");
		std::string dataStream;

		for (size_t i = 0; i < matchDataEntries.size(); i++)
		{

			if (matchDataEntries[i].bMeme == true)
			{
				dataStream = dataStream
					+ uniquePageEntries[matchDataEntries[i].laterPageEntryIndexNumber].year + "\t"
					+ uniquePageEntries[matchDataEntries[i].laterPageEntryIndexNumber].month + "\t"
					+ uniquePageEntries[matchDataEntries[i].laterPageEntryIndexNumber].day + "\t"
					+ uniquePageEntries[matchDataEntries[i].laterPageEntryIndexNumber].title + "\t"
					+ uniquePageEntries[matchDataEntries[i].laterPageEntryIndexNumber].pageNumber + "\t"
					+ uniquePageEntries[matchDataEntries[i].earlierPageEntryIndexNumber].year + "\t"
					+ uniquePageEntries[matchDataEntries[i].earlierPageEntryIndexNumber].month + "\t"
					+ uniquePageEntries[matchDataEntries[i].earlierPageEntryIndexNumber].day + "\t"
					+ uniquePageEntries[matchDataEntries[i].earlierPageEntryIndexNumber].title + "\t"
					+ uniquePageEntries[matchDataEntries[i].earlierPageEntryIndexNumber].pageNumber
					+ "\n";
				//std::ofstream memeData(outputs + "memes\\" + focus, std::ios::app);
			}
			memeData << dataStream;
			dataStream = "";
		}

		// Directed Links, Evolutionary Dead Ends and Average Word Count per Page
		std::ofstream directedLinkData(inputFileStructureLocation + "\\outputs\\" + "directedLinks\\" + processVariables.stringOfYear + "_" + processVariables.stringOfMonth + ".tsv");
		std::string directedLinkStream = "";
		std::ofstream evolutionaryDeadEndData(inputFileStructureLocation + "\\outputs\\" + "evolutionarydeadends\\" + processVariables.stringOfYear + "_" + processVariables.stringOfMonth + ".tsv");
		std::string evolutionaryDeadEndStream = "";
		std::ofstream wordCountDataOfPage(inputFileStructureLocation + "\\outputs\\" + "wordcount_page\\" + processVariables.stringOfYear + "_" + processVariables.stringOfMonth + ".tsv");
		std::string wordCountOfPageStream = "";

		for (size_t j = 0; j < uniquePageEntries.size(); j++)
		{
			if (uniquePageEntries[j].bDirectedLinkMonth == true)
			{

				// Directed Links
				if (uniquePageEntries[j].bestDirectLinkofPage > -1)
				{
					directedLinkStream = directedLinkStream
						+ uniquePageEntries[j].year + "\t"
						+ uniquePageEntries[j].month + "\t"
						+ uniquePageEntries[j].day + "\t"
						+ uniquePageEntries[j].title + "\t"
						+ uniquePageEntries[j].pageNumber + "\t"
						+ uniquePageEntries[uniquePageEntries[j].bestDirectLinkofPage].year + "\t"
						+ uniquePageEntries[uniquePageEntries[j].bestDirectLinkofPage].month + "\t"
						+ uniquePageEntries[uniquePageEntries[j].bestDirectLinkofPage].day + "\t"
						+ uniquePageEntries[uniquePageEntries[j].bestDirectLinkofPage].title + "\t"
						+ uniquePageEntries[uniquePageEntries[j].bestDirectLinkofPage].pageNumber + "\n";
				}

				// Evolutionary Dead Ends
				else
				{
					if (uniquePageEntries[j].month == processVariables.stringOfMonth)
					{
						evolutionaryDeadEndStream = evolutionaryDeadEndStream
							+ uniquePageEntries[j].year + "\t"
							+ uniquePageEntries[j].month + "\t"
							+ uniquePageEntries[j].day + "\t"
							+ uniquePageEntries[j].title + "\t"
							+ uniquePageEntries[j].pageNumber + "\n";
					}
				}
			}

			// Maximum Average Word Counts (and Percentages) per page
			if (uniquePageEntries[j].month == processVariables.stringOfMonth
				&& uniquePageEntries[j].year == processVariables.stringOfYear
				&& uniquePageEntries[j].maximumAverageWordCountofPage > 0)
			{
				wordCountOfPageStream = wordCountOfPageStream
					+ uniquePageEntries[j].year + "\t"
					+ uniquePageEntries[j].month + "\t"
					+ uniquePageEntries[j].day + "\t"
					+ uniquePageEntries[j].title + "\t"
					+ uniquePageEntries[j].pageNumber + "\t"
					+ std::to_string(int(uniquePageEntries[j].maximumAverageWordCountofPage)) + "\t"
					+ std::to_string(uniquePageEntries[j].percentageOfPage)
					+ "\n";
			}
		}

		directedLinkData << directedLinkStream;
		evolutionaryDeadEndData << evolutionaryDeadEndStream;
		wordCountDataOfPage << wordCountOfPageStream;

		// Maximum Average Word Counts (and Percentages) per issue
		std::ofstream wordCountDataOfIssue(inputFileStructureLocation + "\\outputs\\" + "wordcount_issue\\" + processVariables.stringOfYear + "_" + processVariables.stringOfMonth + ".tsv");
		std::string wordCountOfIssueStream = "";

		for (size_t k = 0; k < averageWordCountofIssueList.size(); k++)
		{
			size_t l = averageWordCountofIssueList[k].pagesInIssue[0];

			if (uniquePageEntries[l].month == processVariables.stringOfMonth
				&& uniquePageEntries[l].year == processVariables.stringOfYear
				&& uniquePageEntries[l].maximumAverageWordCountofIssue > 0
				)
			{
				wordCountOfIssueStream = wordCountOfIssueStream
					+ uniquePageEntries[l].year + "\t"
					+ uniquePageEntries[l].month + "\t"
					+ uniquePageEntries[l].day + "\t"
					+ uniquePageEntries[l].title + "\t"
					+ std::to_string(int(uniquePageEntries[l].maximumAverageWordCountofIssue)) + "\t"
					+ std::to_string(uniquePageEntries[l].percenageOfIssue)
					+ "\n";
			}
		}
		wordCountDataOfIssue << wordCountOfIssueStream;

		// Page Percentages By Title

		// Issue Percentages By Title

	}

//    _____                _   
//   |  __ \              | |  
//   | |__) |___  ___  ___| |_ 
//   |  _  // _ \/ __|/ _ \ __|
//   | | \ \  __/\__ \  __/ |_ 
//   |_|  \_\___||___/\___|\__|
//                             

	// general processes
	void clearVectors() {
		uniquePageEntries.clear();
		uniquePageIDs.clear();
		uniqueIssueIDs.clear();
		fullWordCountEntries.clear();
		fullWordCountEntries_UniquePageIDs.clear();
		averageWordCountofIssueList.clear();
		matchDataEntries.clear();
		normalisedTitlesTable.clear();
	}
};
