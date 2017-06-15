#include "stdafx.h"
#include "coresettings.h"
#include "inputter.h"
#include "dateutil.h"

vector<comparisonEntry> comparisonsTable; //vector for comparison calculations
comparisonEntry emptyComparison; //this is used to initialise new entries in the comparisons vector using push_back
vector<uniquePageEntry> uniquePagesTable; //vector containing the UI of all the unique articles that meet minimum requirements
uniquePageEntry emptyPage; //used to initialise new entries in the results vector using push_back
size_t temporaryIteratorHolder = 0;
bool bIsLaterPageAddedToUniqueArticleTable = false; //mark target as uncompared
bool bIsEarlierPageAddedToUniqueArticleTable = false; //mark source as uncompared
void transferCopyfindData(int i, size_t j)
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
void checkForUniqueLaterPage(int i)
{
	string id = copyfindTable[i].normalisedNameOfLeftPage;
	auto pred = [id](const uniquePageEntry & item) {return item.nameOfLaterPage == id;};
	if (find_if(begin(uniquePagesTable), end(uniquePagesTable), pred) != end(uniquePagesTable))
	{}
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