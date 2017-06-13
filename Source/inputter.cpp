#pragma once
#include "stdafx.h"
#include "coresettings.h"

// Input Functions
void makeCopyFindTable(string inputFileStructureLocation, string stringOfCurrentYear, string stringOfCurrentMonth, string stringOfPreviousYear, string stringOfPreviousMonth)
{
	int inputPerfectMatch;
	int inputLeftMatch;
	int inputRightMatch;
	string inputPathOfLeftFile;
	string inputPathOfRightFile;
	copyfindEntry empty;
	ifstream dateForPreviousMonth(inputFileStructureLocation
		+ "\\inputs\\rawmatchingreports\\"
		+ stringOfPreviousYear
		+ "_"
		+ stringOfPreviousMonth
		+ ".txt");
	ifstream dataForCurrentMonth(inputFileStructureLocation
		+ "\\inputs\\rawmatchingreports\\"
		+ stringOfCurrentYear
		+ "_"
		+ stringOfCurrentMonth + ".txt");
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
		string yearOfLeftPage = inputPathOfLeftFile.substr(23, 4);
		string monthOfLeftPage = inputPathOfLeftFile.substr(28, 2);
		string dayOfLeftPage = inputPathOfLeftFile.substr(31, 2);
		string yearOfRightPage = inputPathOfRightFile.substr(23, 4);
		string monthOfRightPage = inputPathOfRightFile.substr(28, 2);
		string dayOfRightPage = inputPathOfRightFile.substr(31, 2);


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
void makeWordCountTable(string inputFileStructureLocation, string stringOfCurrentYear, string stringOfCurrentMonth, string stringOfSubsequentYear, string stringOfSubsequentMonth, string stringOfPreviousYear, string stringOfPreviousMonth)
{
	wordCountTableEntry empty;
	ifstream dataOfPreviousMonth(inputFileStructureLocation + "\\inputs\\wctables\\" + stringOfPreviousYear + "_" + stringOfPreviousMonth + ".tsv");
	ifstream dataOfCurrentMonth(inputFileStructureLocation + "\\inputs\\wctables\\" + stringOfCurrentYear + "_" + stringOfCurrentMonth + ".tsv");
	ifstream Data2(inputFileStructureLocation + "\\inputs\\wctables\\" + stringOfSubsequentYear + "_" + stringOfSubsequentMonth + ".tsv");
	string inputNameOfPage;
	double inputWordCountOfPage;
	string inputNameOfIssue;
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
void makeNormalisedTitleTable(string inputFileStructureLocation)
{
	ifstream data(inputFileStructureLocation + "\\inputs\\NormalisedTitlesns.tsv");
	string title = "";
	string normalisedTitle = "";
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
