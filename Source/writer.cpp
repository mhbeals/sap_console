#pragma once
#include "stdafx.h"
#include "coresettings.h"



// Writing Functions
void writeComparisonTable(string inputlocation, string syear, string smonth)
{
	string data = "";

	ofstream file(inputlocation + "\\outputs\\memes\\" + syear + "_" + smonth + ".tsv"); //print raw comparison table

	for (int i = 0; i < size(comparisonsTable); ++i)
	{
		if (comparisonsTable[i].earlierPage.normalisedNameOfPage.substr(5, 2) == smonth) // if earlier version is within the correct month
		{
			std::transform(comparisonsTable[i].laterPage.titleOfPage.begin(), comparisonsTable[i].laterPage.titleOfPage.end(), comparisonsTable[i].laterPage.titleOfPage.begin(), [](char ch) {return ch == '|' ? ' ' : ch; });
			std::transform(comparisonsTable[i].earlierPage.titleOfPage.begin(), comparisonsTable[i].earlierPage.titleOfPage.end(), comparisonsTable[i].earlierPage.titleOfPage.begin(), [](char ch) {return ch == '|' ? ' ' : ch; });
			data = data + comparisonsTable[i].laterPage.normalisedNameOfPage.substr(0, 4) + "\t" + comparisonsTable[i].laterPage.normalisedNameOfPage.substr(5, 2) + "\t" + comparisonsTable[i].laterPage.normalisedNameOfPage.substr(8, 2) + "\t";
			data = data + comparisonsTable[i].laterPage.titleOfPage + "\t" + comparisonsTable[i].laterPage.pageNumberOfPage + "\t";
			data = data + comparisonsTable[i].earlierPage.normalisedNameOfPage.substr(0, 4) + "\t" + comparisonsTable[i].earlierPage.normalisedNameOfPage.substr(5, 2) + "\t" + comparisonsTable[i].earlierPage.normalisedNameOfPage.substr(8, 2) + "\t";
			data = data + comparisonsTable[i].earlierPage.titleOfPage + "\t" + comparisonsTable[i].earlierPage.pageNumberOfPage + "\n";
		}
	}
	file << data;
	return;
}
void writeDirectedLinksFiles(string inputlocation, string syear, string smonth)
{
	string dldata = "";
	string dedata = "";
	regex t("([A-Za-z-,'&]+)_[A-Z0-9_]{4}");
	regex p("[A-Za-z-,'&]+_([A-Z0-9_]{4})");

	ofstream dlfile(inputlocation + "\\outputs\\directedlinks\\" + syear + "_" + smonth + ".tsv"); //print ancestor-descendent pairs into file
	ofstream defile(inputlocation + "\\outputs\\evolutionarydeadends\\" + syear + "_" + smonth + ".tsv"); //print list of evolutionary dead-ends

	for (int i = 0; i < size(uniquePagesTable); ++i)
	{
		if (!uniquePagesTable[i].bHasNoDescendents&&uniquePagesTable[i].nameOfLaterPage.substr(5, 2) == smonth)
		{
			dldata = dldata + uniquePagesTable[i].nameOfLaterPage.substr(0, 4) + "\t" + uniquePagesTable[i].nameOfLaterPage.substr(5, 2) + "\t" + uniquePagesTable[i].nameOfLaterPage.substr(8, 2) + "\t";
			dldata = dldata + regex_replace(uniquePagesTable[i].nameOfLaterPage.substr(11), t, "$1") + "\t" + regex_replace(uniquePagesTable[i].nameOfLaterPage.substr(11), p, "$1") + "\t";
			dldata = dldata + uniquePagesTable[i].nameOfEarlierPage.substr(0, 4) + "\t" + uniquePagesTable[i].nameOfEarlierPage.substr(5, 2) + "\t" + uniquePagesTable[i].nameOfEarlierPage.substr(8, 2) + "\t";
			dldata = dldata + regex_replace(uniquePagesTable[i].nameOfEarlierPage.substr(11), t, "$1") + "\t" + regex_replace(uniquePagesTable[i].nameOfEarlierPage.substr(11), p, "$1") + "\n";
		}
	}
	for (int i = 0; i < size(uniquePagesTable); ++i)
	{
		if (uniquePagesTable[i].bHasNoDescendents&&uniquePagesTable[i].nameOfLaterPage.substr(5, 2) == smonth)
		{
			dedata = dedata + uniquePagesTable[i].nameOfLaterPage.substr(0, 4) + "\t" + uniquePagesTable[i].nameOfLaterPage.substr(5, 2) + "\t" + uniquePagesTable[i].nameOfLaterPage.substr(8, 2) + "\t";
			dedata = dedata + regex_replace(uniquePagesTable[i].nameOfLaterPage.substr(11, uniquePagesTable[i].nameOfLaterPage.length()), t, "$1") + "\t" + regex_replace(uniquePagesTable[i].nameOfLaterPage.substr(11, uniquePagesTable[i].nameOfLaterPage.length()), p, "$1") + "\n";
		}
	}
	dlfile << dldata;
	defile << dedata;
	return;
}
void writeMaxMatchList(string inputlocation, string syear, string smonth)
{
	string outputraw = (inputlocation + "\\outputs\\wordcounts\\" + syear + "_" + smonth + ".tsv");
	string lines = "";
	ofstream matchfile(outputraw);

	for (int m = 0; m < uniquePagesTable.size(); m++)
	{
		if (uniquePagesTable[m].nameOfLaterPage.substr(5, 2) == smonth)
		{
			if (uniquePagesTable[m].maximumAverageWordCountForReprintsOnLaterPage != 0)
			{
				lines += uniquePagesTable[m].nameOfLaterPage + "\t" + to_string(int(uniquePagesTable[m].maximumAverageWordCountForReprintsOnLaterPage)) + "\n";
			}
		}
		m = m + 1;
	}
	matchfile << lines;
}
void writePagePercentageFiles(string inputlocation, string syear, string smonth)
{
	string lines = "";
	ofstream file(inputlocation + "\\outputs\\pagepercentage\\" + syear + "_" + smonth + ".tsv");
	string errorlines = "";
	ofstream errorfile(inputlocation + "\\outputs\\pagepercentage\\error\\" + syear + "_" + smonth + ".tsv");

	for (int i = 0; i < size(uniquePagesTable); ++i)
	{
		if (uniquePagesTable[i].nameOfLaterPage.substr(5, 2) == smonth)
		{
			if (uniquePagesTable[i].percentageOfReprintedMaterialOnPage >= 1 || uniquePagesTable[i].percentageOfReprintedMaterialOnPage <= 0)
			{
				if (uniquePagesTable[i].nameOfLaterPage != "")
				{
					errorlines += uniquePagesTable[i].nameOfLaterPage + "\n";
				}
			}
			else
			{
				lines += uniquePagesTable[i].nameOfLaterPage + "\t" + to_string(uniquePagesTable[i].percentageOfReprintedMaterialOnPage) + "\n";
			}
		}
	}
	file << lines;
	errorfile << errorlines;
}
void writeIssuePercentageFiles(string inputlocation, string syear, string smonth)
{
	string lines = "";
	ofstream file(inputlocation + "\\outputs\\issuepercentage\\" + syear + "_" + smonth + ".tsv");
	string errorlines = "";
	ofstream errorfile(inputlocation + "\\outputs\\issuepercentage\\error\\" + syear + "_" + smonth + ".tsv");


	for (int i = 0; i < size(uniquePagesTable); ++i)
	{
		if (uniquePagesTable[i].nameOfLaterPage.substr(5, 2) == smonth)
		{
			if (i == 0)
			{
				if (uniquePagesTable[i].percentageOfReprintedMaterialInIssue >= 1 || uniquePagesTable[i].percentageOfReprintedMaterialInIssue <= 0 && uniquePagesTable[i].nameOfIssue != "")
				{
					if (uniquePagesTable[i].nameOfIssue != "")
					{
						errorlines += uniquePagesTable[i].nameOfIssue
							+ "\t"
							+ to_string(uniquePagesTable[i].combinedAverageWordCountForIssue)
							+ "\t"
							+ to_string(uniquePagesTable[i].fullWordCountOfIssue)
							+ "\t"
							+ to_string(uniquePagesTable[i].percentageOfReprintedMaterialInIssue)
							+ "\n";
					}
				}
				else
				{
					if (uniquePagesTable[i].nameOfIssue != "")
					{
						lines += uniquePagesTable[i].nameOfIssue
							+ "\t"
							+ to_string(uniquePagesTable[i].percentageOfReprintedMaterialInIssue)
							+ "\n";
					}
				}
			}
			else if (i > 0)
			{
				if (uniquePagesTable[i].nameOfIssue != uniquePagesTable[i - 1].nameOfIssue)
				{
					if (uniquePagesTable[i].percentageOfReprintedMaterialInIssue >= 1 || uniquePagesTable[i].percentageOfReprintedMaterialInIssue <= 0 && uniquePagesTable[i].nameOfIssue != "")
					{
						if (uniquePagesTable[i].nameOfIssue != "")
						{
							errorlines += uniquePagesTable[i].nameOfIssue
								+ "\t"
								+ to_string(uniquePagesTable[i].combinedAverageWordCountForIssue)
								+ "\t"
								+ to_string(uniquePagesTable[i].fullWordCountOfIssue)
								+ "\t"
								+ to_string(uniquePagesTable[i].percentageOfReprintedMaterialInIssue)
								+ "\n";
						}
					}
					else
					{
						if (uniquePagesTable[i].nameOfIssue != "")
						{
							lines += uniquePagesTable[i].nameOfIssue
								+ "\t"
								+ to_string(uniquePagesTable[i].percentageOfReprintedMaterialInIssue)
								+ "\n";
						}
					}
				}
			}
			else
			{
				if (uniquePagesTable[i].percentageOfReprintedMaterialInIssue >= 1 || uniquePagesTable[i].percentageOfReprintedMaterialInIssue <= 0)
				{
					if (uniquePagesTable[i].nameOfIssue != "")
					{
						stringstream errors;
						errors << uniquePagesTable[i].nameOfIssue;
						errorlines += errors.str();
						errorlines += "\n";
					}
				}
				else
				{
					stringstream ss;
					ss << uniquePagesTable[i].nameOfIssue << "\t" << uniquePagesTable[i].percentageOfReprintedMaterialInIssue;
					lines += ss.str();
					lines += "\n";
				}
			}
		}
	}
	file << lines;
	errorfile << errorlines;
}
void writeTitlePagePercentageFiles(string inputlocation, string syear, string smonth)
{
	ifstream data(inputlocation + "\\inputs\\NormalisedTitlesns.tsv");
	string title = "";
	string ntitle = "";

	while (data >> title >> ntitle)
	{
		string lines = "";
		ofstream file(inputlocation + "\\outputs\\titles\\pagepercentage\\" + ntitle + "\\" + syear + "_" + smonth + ".tsv");
		string errorlines = "";
		ofstream errorfile(inputlocation + "\\outputs\\titles\\pagepercentage\\error\\" + ntitle + "\\" + syear + "_" + smonth + ".tsv");

		for (int i = 0; i < size(uniquePagesTable); ++i)
		{
			if (uniquePagesTable[i].nameOfEarlierPage != ""&&uniquePagesTable[i].nameOfLaterPage.substr(5, 2) == smonth)
			{
				if (uniquePagesTable[i].nameOfLaterPage.find(ntitle) != string::npos)
				{
					if (uniquePagesTable[i].percentageOfReprintedMaterialOnPage >= 1 || uniquePagesTable[i].percentageOfReprintedMaterialOnPage <= 0 && uniquePagesTable[i].nameOfLaterPage != "")
					{
						if (uniquePagesTable[i].nameOfLaterPage != "")
						{
							errorlines += uniquePagesTable[i].nameOfLaterPage + "\n";
						}
					}
					else
					{
						if (uniquePagesTable[i].nameOfLaterPage != "")
						{
							lines += uniquePagesTable[i].nameOfLaterPage + "\t" + to_string(uniquePagesTable[i].percentageOfReprintedMaterialOnPage) + "\n";
						}
					}
				}
			}
		}
		file << lines;
		errorfile << errorlines;
	}
}
void writeTitleIssuePercentageFiles(string inputlocation, string syear, string smonth)
{
	ifstream data(inputlocation + "\\inputs\\NormalisedTitlesns.tsv");
	string title = "";
	string ntitle = "";

	while (data >> title >> ntitle)
	{
		string lines = "";
		ofstream file(inputlocation + "\\outputs\\titles\\issuepercentage\\" + ntitle + "\\" + syear + "_" + smonth + ".tsv");
		string errorlines = "";
		ofstream errorfile(inputlocation + "\\outputs\\titles\\issuepercentage\\" + ntitle + "\\" + syear + "_" + smonth + ".tsv");
		for (int i = 0; i < size(uniquePagesTable); ++i)
		{
			if (uniquePagesTable[i].nameOfEarlierPage != ""&&uniquePagesTable[i].nameOfLaterPage.substr(5, 2) == smonth)
			{

				if (uniquePagesTable[i].nameOfLaterPage.find(ntitle) != string::npos)
				{
					if (i > 0)
					{
						if (uniquePagesTable[i].nameOfIssue != uniquePagesTable[i - 1].nameOfIssue)
						{
							if (uniquePagesTable[i].percentageOfReprintedMaterialInIssue >= 1 || uniquePagesTable[i].percentageOfReprintedMaterialInIssue <= 0 && uniquePagesTable[i].nameOfIssue != "")
							{
								if (uniquePagesTable[i].nameOfIssue != "")
								{
									errorlines += uniquePagesTable[i].nameOfIssue + "\n";
								}
							}
							else
							{
								if (uniquePagesTable[i].nameOfIssue != "")
								{
									lines += uniquePagesTable[i].nameOfIssue + "\t" + to_string(uniquePagesTable[i].percentageOfReprintedMaterialInIssue) + "\n";
								}
							}
						}
					}
					else
					{
						if (uniquePagesTable[i].percentageOfReprintedMaterialInIssue >= 1 || uniquePagesTable[i].percentageOfReprintedMaterialInIssue <= 0)
						{
							if (uniquePagesTable[i].nameOfIssue != "")
							{
								stringstream errors;
								errors << uniquePagesTable[i].nameOfIssue;
								errorlines += errors.str();
								errorlines += "\n";
							}
						}
						else
						{
							stringstream ss;
							ss << uniquePagesTable[i].nameOfIssue << "\t" << uniquePagesTable[i].percentageOfReprintedMaterialInIssue;
							lines += ss.str();
							lines += "\n";
						}
					}
				}
			}
		}

		file << lines;
		errorfile << errorlines;
	}
}