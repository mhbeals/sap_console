// Scissors and Paste Console
<<<<<<< HEAD
// M. H. Beals (2017) v.0.2.1 [Software]

// MIT License
// Copyright(c) 2017 M. H. Beals
=======
// M. H. Beals (2017) v.0.1.7 [Software]

// MIT License

// Copyright(c) 2017 M. H. Beals

>>>>>>> origin/master
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files(the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// // to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions :
<<<<<<< HEAD
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
=======

// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.

>>>>>>> origin/master
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include "stdafx.h"
#include "dateutil.h"
#include "processes.h"
<<<<<<< HEAD
#include "inputter.h"
#include "coresettings.h"

// Common Variables
string inputFileStructureLocation = "E:\\Documents\\Notebooks\\Reprinting\\NewSAPConsole";
string stringOfPreviousYear = "";
string stringOfYear = "";
string stringOfSubsequentYear = "";
string stringOfPreviousMonth = "";
string stringOfMonth = "";
string stringOfSubsequentMonth = "";

int inputStartYear = 1800;
int inputEndYear = 1800;
int assumedStartMonth = 1;
int processingSwitch = 0;
string promptContainer = "";

string varList(int yearBeingProcessed, int monthBeingProcessed)
{
	if (monthBeingProcessed == 1)
	{
		ostringstream listOfMonthsAndYears;
		listOfMonthsAndYears << yearBeingProcessed << ",0" << monthBeingProcessed << "," << yearBeingProcessed << ",0" << monthBeingProcessed + 1 << "," << yearBeingProcessed - 1 << ",12";
		return listOfMonthsAndYears.str();
	}
	else if (monthBeingProcessed < 9)
	{
		ostringstream listOfMonthsAndYears;
		listOfMonthsAndYears << yearBeingProcessed << ",0" << monthBeingProcessed << "," << yearBeingProcessed << ",0" << monthBeingProcessed + 1 << "," << yearBeingProcessed << ",0" << monthBeingProcessed-1;
		return listOfMonthsAndYears.str();
	}
	else if (monthBeingProcessed == 9)
	{
		ostringstream listOfMonthsAndYears;
		listOfMonthsAndYears << yearBeingProcessed << ",0" << monthBeingProcessed << "," << yearBeingProcessed << "," << monthBeingProcessed + 1 << "," << yearBeingProcessed << ",08";
		return listOfMonthsAndYears.str();
	}
	else if (monthBeingProcessed == 10)
	{
		ostringstream listOfMonthsAndYears;
		listOfMonthsAndYears << yearBeingProcessed << "," << monthBeingProcessed << "," << yearBeingProcessed << "," << monthBeingProcessed + 1 << "," << yearBeingProcessed << "," << ",09";
		return listOfMonthsAndYears.str();
	}
	else if (monthBeingProcessed == 11)
	{
		ostringstream listOfMonthsAndYears;
		listOfMonthsAndYears << yearBeingProcessed << "," << monthBeingProcessed << "," << yearBeingProcessed << "," << monthBeingProcessed + 1 << "," << yearBeingProcessed << "," << monthBeingProcessed - 1;
		return listOfMonthsAndYears.str();
	}
	else
	{
		ostringstream listOfMonthsAndYears;
		listOfMonthsAndYears << yearBeingProcessed << "," << monthBeingProcessed << "," << yearBeingProcessed + 1 << ",01" << "," << yearBeingProcessed << ",11";
		return listOfMonthsAndYears.str();
=======
#include <iostream>
#include <string>

// Common Variables
string inputlocation = "C:\\Reprinting";
string syear = "";
string syear2 = "";
string smonth = "";
string smonth2 = "";
int year = 1800;
int endyear = 1900;
int month = 1;
int process = 0;
string prompt = "";

string varList(int year, int month)
{
	if (month < 9)
	{
		ostringstream list;
		list << year << ",0" << month << "," << year << ",0" << month + 1;
		return list.str();
	}
	else if (month == 9)
	{
		ostringstream list;
		list << year << ",0" << month << "," << year << "," << month + 1;
		return list.str();
	}
	else if (month == 10 || month == 11)
	{
		ostringstream list;
		list << year << "," << month << "," << year << "," << month + 1;
		return list.str();
	}
	else
	{
		ostringstream list;
		list << year << "," << month << "," << year + 1 << ",01";
		return list.str();
>>>>>>> origin/master
	}
}

int main()
{
	cout << "Welcome to the Scissors and Paste Console." << endl;
	cout << "Available processes:" << endl;
	cout << "1. Create List(s) of Memes" << endl;
	cout << "2. Create List(s) of Directed Links" << endl;
	cout << "3. Create List(s) of Average Matching Word Count" << endl;
	cout << "4. Create List(s) of the Percentage of Duplicate Material per Page" << endl; 
	cout << "5. Create List(s) of the Percentage of Duplicate Material per Issue" << endl;
	cout << "6. Create List(s) of the Percentage of Duplicate Material per Page per Title" << endl;
	cout << "7. Create List(s) of the Percentage of Duplicate Material per Issue per Title" << endl;
	cout << "8. Everything" << endl;
	cout << "Which processes would you like to undertake?" << endl;
<<<<<<< HEAD
	cin >> processingSwitch;
	
	cout << "Your pre-set variables are:" << endl;
	cout << "Starting Year: " << inputStartYear << endl;
	cout << "Ending Year: " << inputEndYear << endl;
	cout << "File Structure Location: " << inputFileStructureLocation << endl;
	cout << "Would you like to change the standard variables?" << endl;
	cin >> promptContainer;
	if (promptContainer == "y")
	{
		cout << "Starting Year? ";
		cin >> inputStartYear;
		cout << endl << "Ending Year? ";
		cin >> inputEndYear;
		cout << endl << "Input Location? ";
		cin >> inputFileStructureLocation;
		cout << inputFileStructureLocation << endl;
=======
	cin >> process;
	
	cout << "Your pre-set variables are:" << endl;
	cout << "Starting Year: " << year << endl;
	cout << "Ending Year: " << endyear << endl;
	cout << "File Structure Location: " << inputlocation << endl;
	cout << "Would you like to change the standard variables?" << endl;
	cin >> prompt;
	if (prompt == "y")
	{
		cout << "Starting Year? ";
		cin >> year;
		cout << endl << "Ending Year? ";
		cin >> endyear;
		cout << endl << "Input Location? ";
		cin >> inputlocation;
		cout << inputlocation << endl;
>>>>>>> origin/master
	}
	else
	{
		cout << "Keeping standard variables..." << endl;
	}
	
<<<<<<< HEAD
	for (int i = inputStartYear; i < inputEndYear + 1; i++)
	{
		inputStartYear = i;

		cout << "Processing " << inputStartYear << "...";
		
		for (int j = assumedStartMonth; j < 13; j++)
		{
			assumedStartMonth = j;
			cout << getMonth(assumedStartMonth) << "...";

			// Establish Variables
			string listOfMonthsAndYears = varList(inputStartYear, assumedStartMonth);
			stringOfYear = listOfMonthsAndYears.substr(0, 4);
			stringOfMonth = listOfMonthsAndYears.substr(5, 2);
			stringOfSubsequentYear = listOfMonthsAndYears.substr(8, 4);
			stringOfSubsequentMonth = listOfMonthsAndYears.substr(13, 2);
			stringOfPreviousYear = listOfMonthsAndYears.substr(16, 4);
			stringOfPreviousMonth = listOfMonthsAndYears.substr(21, 2);

			// Process Data
			makeCopyFindTable(inputFileStructureLocation, stringOfYear, stringOfMonth, stringOfPreviousYear, stringOfPreviousMonth); // Add new smonth/years to all
			makeNormalisedTitleTable(inputFileStructureLocation);
			regexCopyfindTableTitles();
			makeComparisonsTable();

			switch(processingSwitch)
			{
			case 1:	
				writeComparisonTable(inputFileStructureLocation, stringOfYear, stringOfMonth);
			case 2:
				processDirectLinkComparisons(); 
				writeDirectedLinksFiles(inputFileStructureLocation, stringOfYear, stringOfMonth);
			case 3:
				makeWordCountTable(inputFileStructureLocation, stringOfYear, stringOfMonth, stringOfSubsequentYear, stringOfSubsequentMonth, stringOfPreviousYear, stringOfPreviousMonth);
				crossReferenceValuesInWordCountAndCopyfindTables();
				assignMaximumAverageWordCountValues(); 
				writeMaxMatchList(inputFileStructureLocation, stringOfYear, stringOfMonth);
			case 4:
				makeWordCountTable(inputFileStructureLocation, stringOfYear, stringOfMonth, stringOfSubsequentYear, stringOfSubsequentMonth, stringOfPreviousYear, stringOfPreviousMonth);
				crossReferenceValuesInWordCountAndCopyfindTables();
				assignMaximumAverageWordCountValues(); 
				writePagePercentageFiles(inputFileStructureLocation, stringOfYear, stringOfMonth);
			case 5:makeWordCountTable(inputFileStructureLocation, stringOfYear, stringOfMonth, stringOfSubsequentYear, stringOfSubsequentMonth, stringOfPreviousYear, stringOfPreviousMonth);
				crossReferenceValuesInWordCountAndCopyfindTables();
				assignMaximumAverageWordCountValues(); 
				writeIssuePercentageFiles(inputFileStructureLocation, stringOfYear, stringOfMonth);
			case 6:makeWordCountTable(inputFileStructureLocation, stringOfYear, stringOfMonth, stringOfSubsequentYear, stringOfSubsequentMonth, stringOfPreviousYear, stringOfPreviousMonth);
				crossReferenceValuesInWordCountAndCopyfindTables();
				assignMaximumAverageWordCountValues(); 
				writeTitlePagePercentageFiles(inputFileStructureLocation, stringOfYear, stringOfMonth);
			case 7:makeWordCountTable(inputFileStructureLocation, stringOfYear, stringOfMonth, stringOfSubsequentYear, stringOfSubsequentMonth, stringOfPreviousYear, stringOfPreviousMonth);
				crossReferenceValuesInWordCountAndCopyfindTables();
				assignMaximumAverageWordCountValues(); 
				writeTitleIssuePercentageFiles(inputFileStructureLocation, stringOfYear, stringOfMonth);
			case 8:processDirectLinkComparisons();
				makeWordCountTable(inputFileStructureLocation, stringOfYear, stringOfMonth, stringOfSubsequentYear, stringOfSubsequentMonth, stringOfPreviousYear, stringOfPreviousMonth);
				crossReferenceValuesInWordCountAndCopyfindTables();
				assignMaximumAverageWordCountValues();
				writeComparisonTable(inputFileStructureLocation, stringOfYear, stringOfMonth);
				writeDirectedLinksFiles(inputFileStructureLocation, stringOfYear, stringOfMonth);
				writeMaxMatchList(inputFileStructureLocation, stringOfYear, stringOfMonth);
				writePagePercentageFiles(inputFileStructureLocation, stringOfYear, stringOfMonth);
				writeIssuePercentageFiles(inputFileStructureLocation, stringOfYear, stringOfMonth);
				writeTitlePagePercentageFiles(inputFileStructureLocation, stringOfYear, stringOfMonth);
				writeTitleIssuePercentageFiles(inputFileStructureLocation, stringOfYear, stringOfMonth);
			};

			clearVectors(); // clear RAM
		}
		assumedStartMonth = 1;
=======
	for (int i = year; i < endyear + 1; i++)
	{
		year = i;

		cout << "Processing " << year << "...";
		
		for (int j = month; j < 13; j++)
		{
			month = j;
			cout << getMonth(month) << "...";

			// Establish Variables
			string vList = varList(year, month);
			syear = vList.substr(0, 4);
			smonth = vList.substr(5, 2);
			syear2 = vList.substr(8, 4);
			smonth2 = vList.substr(13, 2);
	
			// Process Data
			makeCFTable(inputlocation, syear, smonth);
			makeNTTable(inputlocation);
			regexCopyfind();
			makecomparisonsTable();

			switch(process)
			{
			case 1:	
				writeComparisonTable(inputlocation, syear, smonth);
			case 2:
				processDLcomparisons(); 
				writeDirectedLinksTables(inputlocation, syear, smonth);
			case 3:
				makeBLTable(inputlocation, syear, smonth, syear2, smonth2);
				crossReferenceValues();
				processMaximumValues(); 
				writeMaxMatchList(inputlocation, syear, smonth);
			case 4:
				makeBLTable(inputlocation, syear, smonth, syear2, smonth2);
				crossReferenceValues();
				processMaximumValues(); 
				writePagePercentage(inputlocation, syear, smonth);
			case 5:makeBLTable(inputlocation, syear, smonth, syear2, smonth2);
				crossReferenceValues();
				processMaximumValues(); 
				writeIssuePercentage(inputlocation, syear, smonth);
			case 6:makeBLTable(inputlocation, syear, smonth, syear2, smonth2);
				crossReferenceValues();
				processMaximumValues(); 
				writeTitlePagePercentage(inputlocation, syear, smonth);
			case 7:makeBLTable(inputlocation, syear, smonth, syear2, smonth2);
				crossReferenceValues();
				processMaximumValues(); 
				writeTitleIssuePercentage(inputlocation, syear, smonth);
			case 8:processDLcomparisons();
				makeBLTable(inputlocation, syear, smonth, syear2, smonth2);
				crossReferenceValues();
				processMaximumValues();
				writeComparisonTable(inputlocation, syear, smonth);
				writeDirectedLinksTables(inputlocation, syear, smonth);
				writeMaxMatchList(inputlocation, syear, smonth);
				writePagePercentage(inputlocation, syear, smonth);
				writeIssuePercentage(inputlocation, syear, smonth);
				writeTitlePagePercentage(inputlocation, syear, smonth);
				writeTitleIssuePercentage(inputlocation, syear, smonth);
			};
		
			
			

			// Clear RAM
			clearVectors();
		}
		month = 1;
>>>>>>> origin/master
		cout << "finished " << endl;
	}
	system("pause"); 
	return 0;
}