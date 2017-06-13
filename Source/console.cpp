// Scissors and Paste Console
// M. H. Beals (2017) v.0.2.1 [Software]

// MIT License
// Copyright(c) 2017 M. H. Beals
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files(the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// // to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions :
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
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
	}
	else
	{
		cout << "Keeping standard variables..." << endl;
	}
	
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
		cout << "finished " << endl;
	}
	system("pause"); 
	return 0;
}