#pragma once
#include "coresettings.h"
#include "inputter.h"

class processor : public inputter
{
public:

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
	void makeComparisonsTable()

	{

		int maxDaysBetweenLaterAndEarlierPages = 21; //up to 1 year maximum, otherwise change the comparison logic

		int leftMatchTolerance = 90; //minimum left match

		int rightMatchTolerance = 90; //minimum right match

		int perfectMatchTolerance = 160; //minimum overall or perfect match



		for (int i = 0; i < size(copyfindTable); i++) //while data is available

		{

			//do not include matches from same title

			if (copyfindTable[i].titleOfLeftPage == copyfindTable[i].titleOfRightPage) {}



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
		for (int i = 0; i < uniquePagesTable.size(); i++)
		{
			if (i < 65)
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
			else
			{
				int testmaxval = copyfindTable[i].copyfindAverageMatch; // set test wordcount to i

				for (int j =i-64; j < i+64; j++)
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

		}

		for (int k = 0; k < uniquePagesTable.size(); k++)
		{
			if (k < 65)
			{
				// go through unique articles
				for (int l = 0; l < k + 64; l++)
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
			else
			{
				// go through unique articles
				for (int l = k-64; l < k + 64; l++)
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
		}
		double testIssueSum = 0;
		for (int k = 0; k < uniquePagesTable.size(); k++)
		{
			testIssueSum = uniquePagesTable[k].maximumAverageWordCountForReprintsOnLaterPage;
			// go through unique articles
			if (k < 65)
			{
				for (int l = 0; l < k+64; l++)
				{
					// go through copyfind table
					if (uniquePagesTable[k].nameOfIssue == uniquePagesTable[l].nameOfIssue
						&&
						uniquePagesTable[k].nameOfLaterPage != uniquePagesTable[l].nameOfLaterPage)
					{
						testIssueSum += uniquePagesTable[l].maximumAverageWordCountForReprintsOnLaterPage;
					}
				}
				uniquePagesTable[k].combinedAverageWordCountForIssue = testIssueSum;
				uniquePagesTable[k].percentageOfReprintedMaterialInIssue = uniquePagesTable[k].combinedAverageWordCountForIssue / uniquePagesTable[k].fullWordCountOfIssue;
			}
			else
			{
				for (int l = k-64; l < k+64; l++)
				{
					// go through copyfind table
					if (uniquePagesTable[k].nameOfIssue == uniquePagesTable[l].nameOfIssue
						&&
						uniquePagesTable[k].nameOfLaterPage != uniquePagesTable[l].nameOfLaterPage)
					{
						testIssueSum += uniquePagesTable[l].maximumAverageWordCountForReprintsOnLaterPage;
					}
				}
				uniquePagesTable[k].combinedAverageWordCountForIssue = testIssueSum;
				uniquePagesTable[k].percentageOfReprintedMaterialInIssue = uniquePagesTable[k].combinedAverageWordCountForIssue / uniquePagesTable[k].fullWordCountOfIssue;
			}
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