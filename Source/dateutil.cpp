#include "stdafx.h"
#include "dateutil.h"
#include "coresettings.h"

string getMonth(int month)
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

int monthToDays(int month, bool isLeapYear) //convert days, months and years into day of that year
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

int dayOfWeek(int year, int month, int day)
{
	// Sakamoto's algorithm 
	static int t[] = { 0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4 };
	year -= month < 3;
	return (year + year / 4 - year / 100 + year / 400 + t[month - 1] + day) % 7;	
}

int findDaysBetweenWithDifferentYears(int i)
{
	int A_Days = monthToDays(copyfindTable[i].monthOfLeftPage, isLeapYear(copyfindTable[i].yearOfLeftPage)) + copyfindTable[i].dayOfLeftPage;//calculate numbers days into target year 
	bool bIsLeapYear = isLeapYear(copyfindTable[i].yearOfRightPage); //determine if the source year is a leap year
	int B_Days = monthToDays(copyfindTable[i].monthOfRightPage, bIsLeapYear) + copyfindTable[i].dayOfRightPage; //calculate the number of days into source year

	if (bIsLeapYear) { B_Days = 366 - B_Days; } //calculate the number of days remaining in leap source year
	else { B_Days = 365 - B_Days; } //calculate the number of days remaining in non-leap source year

	return (A_Days + B_Days);
}

int findDaysBetweenWithSameYears(int i)
{
	int A_Days = monthToDays(copyfindTable[i].monthOfLeftPage, isLeapYear(copyfindTable[i].yearOfLeftPage)) + copyfindTable[i].dayOfLeftPage; //calculate days in target year so far
	int B_Days = monthToDays(copyfindTable[i].monthOfRightPage, isLeapYear(copyfindTable[i].yearOfRightPage)) + copyfindTable[i].dayOfRightPage; //calculate days in source year so far
	return (A_Days - B_Days);
}