#include "stdafx.h"
#include "coresettings.h"

// Date utilities

std::string getMonth(int month)
{
	switch (month)
	{
	case 1: return "January";
	case 2: return "February";
	case 3: return "March";
	case 4: return "April";
	case 5: return "May";
	case 6: return "June";
	case 7: return "July";
	case 8: return "August";
	case 9: return "September";
	case 10: return "October";
	case 11: return "November";
	case 12: return "December";
	default: return "Invalid Month";
	}
}

// Sorting Utilities

bool CompareRecords(const matchDataEntry& a, const matchDataEntry& b)
{
	if (a.earlierEnumeratedDate < b.earlierEnumeratedDate)
		return true;
	else if (a.earlierEnumeratedDate > b.earlierEnumeratedDate)
		return false;

	if (a.earlierTitle < b.earlierTitle)
		return true;
	else if (a.earlierTitle > b.earlierTitle)
		return false;

	if (a.earlierPageNumber < b.earlierPageNumber)
		return true;
	else if (a.earlierPageNumber > b.earlierPageNumber)
		return false;
}
