#pragma once
#include "coresettings.h"
#include "processor.h"

class writer : public processor
{
public:
	// Variables

	std::string data = "";
	std::string data_one = "";
	std::string data_two = "";

	// Writer

	void writeComparisonTable(std::string inputlocation, std::string syear, std::string smonth)
	{
		std::ofstream createfile(inputlocation + "\\outputs\\memes\\" + syear + "_" + smonth + ".tsv");
		std::ofstream datafile(inputlocation + "\\outputs\\memes\\" + syear + "_" + smonth + ".tsv",std::ios::app); //print raw comparison table

		for (int i = 0; i < size(comparisonsTable); ++i)
		{
			if (comparisonsTable[i].earlierPage.normalisedNameOfPage.substr(5, 2) == smonth) // if earlier version is within the correct month
			{
				std::transform(comparisonsTable[i].laterPage.titleOfPage.begin(), comparisonsTable[i].laterPage.titleOfPage.end(), comparisonsTable[i].laterPage.titleOfPage.begin(), [](char ch) {return ch == '|' ? ' ' : ch; });
				std::transform(comparisonsTable[i].earlierPage.titleOfPage.begin(), comparisonsTable[i].earlierPage.titleOfPage.end(), comparisonsTable[i].earlierPage.titleOfPage.begin(), [](char ch) {return ch == '|' ? ' ' : ch; });
				data = comparisonsTable[i].laterPage.normalisedNameOfPage.substr(0, 4) + "\t" + comparisonsTable[i].laterPage.normalisedNameOfPage.substr(5, 2) + "\t" + comparisonsTable[i].laterPage.normalisedNameOfPage.substr(8, 2) + "\t";
				data = data + comparisonsTable[i].laterPage.titleOfPage + "\t" + comparisonsTable[i].laterPage.pageNumberOfPage + "\t";
				data = data + comparisonsTable[i].earlierPage.normalisedNameOfPage.substr(0, 4) + "\t" + comparisonsTable[i].earlierPage.normalisedNameOfPage.substr(5, 2) + "\t" + comparisonsTable[i].earlierPage.normalisedNameOfPage.substr(8, 2) + "\t";
				data = data + comparisonsTable[i].earlierPage.titleOfPage + "\t" + comparisonsTable[i].earlierPage.pageNumberOfPage + "\n";
				datafile << data;
			}
		}
		return;
	}
	void writeDirectedLinksFiles(std::string inputlocation, std::string syear, std::string smonth)
	{
		std::regex t("([A-Za-z-,'&]+)_[A-Z0-9_]{4}");
		std::regex p("[A-Za-z-,'&]+_([A-Z0-9_]{4})");

		std::ofstream createdatafile_one(inputlocation + "\\outputs\\directedlinks\\" + syear + "_" + smonth + ".tsv"); //print ancestor-descendent pairs into file
		std::ofstream createdatafile_two(inputlocation + "\\outputs\\evolutionarydeadends\\" + syear + "_" + smonth + ".tsv"); //print list of evolutionary dead-ends
		std::ofstream datafile_one(inputlocation + "\\outputs\\directedlinks\\" + syear + "_" + smonth + ".tsv", std::ios::app);
		std::ofstream datafile_two(inputlocation + "\\outputs\\evolutionarydeadends\\" + syear + "_" + smonth + ".tsv",std::ios::app); 

		for (int i = 0; i < size(uniquePagesTable); ++i)
		{
			if (!uniquePagesTable[i].bHasNoDescendents&&uniquePagesTable[i].nameOfLaterPage.substr(5, 2) == smonth)
			{
				data_one = uniquePagesTable[i].nameOfLaterPage.substr(0, 4) + "\t" + uniquePagesTable[i].nameOfLaterPage.substr(5, 2) + "\t" + uniquePagesTable[i].nameOfLaterPage.substr(8, 2) + "\t";
				data_one = data_one + std::regex_replace(uniquePagesTable[i].nameOfLaterPage.substr(11), t, "$1") + "\t" + std::regex_replace(uniquePagesTable[i].nameOfLaterPage.substr(11), p, "$1") + "\t";
				data_one = data_one + uniquePagesTable[i].nameOfEarlierPage.substr(0, 4) + "\t" + uniquePagesTable[i].nameOfEarlierPage.substr(5, 2) + "\t" + uniquePagesTable[i].nameOfEarlierPage.substr(8, 2) + "\t";
				data_one = data_one + std::regex_replace(uniquePagesTable[i].nameOfEarlierPage.substr(11), t, "$1") + "\t" + std::regex_replace(uniquePagesTable[i].nameOfEarlierPage.substr(11), p, "$1") + "\n";
				datafile_one << data_one;
			}
		}
		for (int i = 0; i < size(uniquePagesTable); ++i)
		{
			if (uniquePagesTable[i].bHasNoDescendents&&uniquePagesTable[i].nameOfLaterPage.substr(5, 2) == smonth)
			{
				data_two = uniquePagesTable[i].nameOfLaterPage.substr(0, 4) + "\t" + uniquePagesTable[i].nameOfLaterPage.substr(5, 2) + "\t" + uniquePagesTable[i].nameOfLaterPage.substr(8, 2) + "\t";
				data_two = data_two + regex_replace(uniquePagesTable[i].nameOfLaterPage.substr(11, uniquePagesTable[i].nameOfLaterPage.length()), t, "$1") + "\t" + regex_replace(uniquePagesTable[i].nameOfLaterPage.substr(11, uniquePagesTable[i].nameOfLaterPage.length()), p, "$1") + "\n";
				datafile_two << data_two;
			}
		}
		return;
	}
	void writeMaxMatchList(std::string inputlocation, std::string syear, std::string smonth)
	{
		std::ofstream createfile(inputlocation + "\\outputs\\wordcounts\\" + syear + "_" + smonth + ".tsv");
		std::ofstream datafile(inputlocation + "\\outputs\\wordcounts\\" + syear + "_" + smonth + ".tsv",std::ios::app);

		for (int m = 0; m < uniquePagesTable.size(); m++)
		{
			if (uniquePagesTable[m].nameOfLaterPage.substr(5, 2) == smonth)
			{
				if (uniquePagesTable[m].maximumAverageWordCountForReprintsOnLaterPage != 0)
				{
					data = uniquePagesTable[m].nameOfLaterPage + "\t" + std::to_string(int(uniquePagesTable[m].maximumAverageWordCountForReprintsOnLaterPage)) + "\n";
					datafile << data;
				}
			}
		}

	}
	void writePagePercentageFiles(std::string inputlocation, std::string syear, std::string smonth)
	{
		std::ofstream createfile_one(inputlocation + "\\outputs\\pagepercentage\\" + syear + "_" + smonth + ".tsv");
		std::ofstream datafile_one(inputlocation + "\\outputs\\pagepercentage\\" + syear + "_" + smonth + ".tsv",std::ios::app);
		std::ofstream createfile_two(inputlocation + "\\outputs\\pagepercentage\\error\\" + syear + "_" + smonth + ".tsv");
		std::ofstream datafile_two(inputlocation + "\\outputs\\pagepercentage\\error\\" + syear + "_" + smonth + ".tsv",std::ios::app);


		for (int i = 0; i < size(uniquePagesTable); ++i)
		{
			if (uniquePagesTable[i].nameOfLaterPage.substr(5, 2) == smonth)
			{
				if (uniquePagesTable[i].percentageOfReprintedMaterialOnPage >= 1 || uniquePagesTable[i].percentageOfReprintedMaterialOnPage <= 0)
				{
					if (uniquePagesTable[i].nameOfLaterPage != "")
					{
						data_two = uniquePagesTable[i].nameOfLaterPage + "\n";
						datafile_two << data_two;
					}
				}
				else
				{
					data_one = uniquePagesTable[i].nameOfLaterPage + "\t" + std::to_string(uniquePagesTable[i].percentageOfReprintedMaterialOnPage) + "\n";
					datafile_one << data_one;
				}
			}
		}
	}
	void writeIssuePercentageFiles(std::string inputlocation, std::string syear, std::string smonth)
	{
		std::ofstream createfile_one(inputlocation + "\\outputs\\issuepercentage\\" + syear + "_" + smonth + ".tsv");
		std::ofstream createfile_two(inputlocation + "\\outputs\\issuepercentage\\error\\" + syear + "_" + smonth + ".tsv");
		std::ofstream datafile_one(inputlocation + "\\outputs\\issuepercentage\\" + syear + "_" + smonth + ".tsv",std::ios::app);
		std::ofstream datafile_two(inputlocation + "\\outputs\\issuepercentage\\error\\" + syear + "_" + smonth + ".tsv", std::ios::app);


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
							data_two = uniquePagesTable[i].nameOfIssue
								+ "\t"
								+ std::to_string(uniquePagesTable[i].combinedAverageWordCountForIssue)
								+ "\t"
								+ std::to_string(uniquePagesTable[i].fullWordCountOfIssue)
								+ "\t"
								+ std::to_string(uniquePagesTable[i].percentageOfReprintedMaterialInIssue)
								+ "\n";
							datafile_two << data_two;
						}
					}
					else
					{
						if (uniquePagesTable[i].nameOfIssue != "")
						{
							data_one = uniquePagesTable[i].nameOfIssue
								+ "\t"
								+ std::to_string(uniquePagesTable[i].percentageOfReprintedMaterialInIssue)
								+ "\n";
							datafile_one << data_one;
						}
					}
				}
				else
				{
					if (uniquePagesTable[i].nameOfIssue != uniquePagesTable[i - 1].nameOfIssue)
					{
						if (uniquePagesTable[i].percentageOfReprintedMaterialInIssue >= 1 || uniquePagesTable[i].percentageOfReprintedMaterialInIssue <= 0 && uniquePagesTable[i].nameOfIssue != "")
						{
							if (uniquePagesTable[i].nameOfIssue != "")
							{
								data_two = uniquePagesTable[i].nameOfIssue
									+ "\t"
									+ std::to_string(uniquePagesTable[i].combinedAverageWordCountForIssue)
									+ "\t"
									+ std::to_string(uniquePagesTable[i].fullWordCountOfIssue)
									+ "\t"
									+ std::to_string(uniquePagesTable[i].percentageOfReprintedMaterialInIssue)
									+ "\n";
								datafile_two << data_two;
							}
						}
						else
						{
							if (uniquePagesTable[i].nameOfIssue != "")
							{
								data_one = uniquePagesTable[i].nameOfIssue
									+ "\t"
									+ std::to_string(uniquePagesTable[i].percentageOfReprintedMaterialInIssue)
									+ "\n";
								datafile_one << data_one;
							}
						}
					}
				}
			}
		}
	}
	void writeTitlePagePercentageFiles(std::string inputlocation, std::string syear, std::string smonth)
	{
		std::ifstream normalisationfile(inputlocation + "\\inputs\\NormalisedTitlesns.tsv");
		std::string title = "";
		std::string ntitle = "";

		while (normalisationfile >> title >> ntitle)
		{
			std::ofstream createfile_one(inputlocation + "\\outputs\\titles\\pagepercentage\\" + ntitle + "\\" + syear + "_" + smonth + ".tsv");
			std::ofstream datafile_one(inputlocation + "\\outputs\\titles\\pagepercentage\\" + ntitle + "\\" + syear + "_" + smonth + ".tsv");
			std::ofstream createfile_two(inputlocation + "\\outputs\\titles\\pagepercentage\\error\\" + ntitle + "\\" + syear + "_" + smonth + ".tsv");
			std::ofstream datafile_two(inputlocation + "\\outputs\\titles\\pagepercentage\\error\\" + ntitle + "\\" + syear + "_" + smonth + ".tsv");

			for (int i = 0; i < size(uniquePagesTable); ++i)
			{
				if (uniquePagesTable[i].nameOfEarlierPage != ""&&uniquePagesTable[i].nameOfLaterPage.substr(5, 2) == smonth)
				{
					if (uniquePagesTable[i].nameOfLaterPage.find(ntitle) != std::string::npos)
					{
						if (uniquePagesTable[i].percentageOfReprintedMaterialOnPage >= 1 || uniquePagesTable[i].percentageOfReprintedMaterialOnPage <= 0 && uniquePagesTable[i].nameOfLaterPage != "")
						{
							if (uniquePagesTable[i].nameOfLaterPage != "")
							{
								data_two = uniquePagesTable[i].nameOfLaterPage + "\n";
								datafile_two << data_two;
							}
						}
						else
						{
							if (uniquePagesTable[i].nameOfLaterPage != "")
							{
								data_one = uniquePagesTable[i].nameOfLaterPage + "\t" + std::to_string(uniquePagesTable[i].percentageOfReprintedMaterialOnPage) + "\n";
								datafile_one << data_one;
							}
						}
					}
				}
			}
		}
	}
	void writeTitleIssuePercentageFiles(std::string inputlocation, std::string syear, std::string smonth)
	{
		std::ifstream normalisationfile(inputlocation + "\\inputs\\NormalisedTitlesns.tsv");
		std::string title = "";
		std::string ntitle = "";

		while (normalisationfile >> title >> ntitle)
		{
			std::ofstream createfile_one(inputlocation + "\\outputs\\titles\\issuepercentage\\" + ntitle + "\\" + syear + "_" + smonth + ".tsv");
			std::ofstream datafile_one(inputlocation + "\\outputs\\titles\\issuepercentage\\" + ntitle + "\\" + syear + "_" + smonth + ".tsv");
			std::ofstream createfile_two(inputlocation + "\\outputs\\titles\\issuepercentage\\error\\" + ntitle + "\\" + syear + "_" + smonth + ".tsv");
			std::ofstream datafile_two(inputlocation + "\\outputs\\titles\\issuepercentage\\error\\" + ntitle + "\\" + syear + "_" + smonth + ".tsv");
			for (int i = 0; i < size(uniquePagesTable); ++i)
			{
				if (uniquePagesTable[i].nameOfEarlierPage != ""&&uniquePagesTable[i].nameOfLaterPage.substr(5, 2) == smonth)
				{

					if (uniquePagesTable[i].nameOfLaterPage.find(ntitle) != std::string::npos)
					{
						if (i > 0)
						{
							if (uniquePagesTable[i].nameOfIssue != uniquePagesTable[i - 1].nameOfIssue)
							{
								if (uniquePagesTable[i].percentageOfReprintedMaterialInIssue >= 1 || uniquePagesTable[i].percentageOfReprintedMaterialInIssue <= 0 && uniquePagesTable[i].nameOfIssue != "")
								{
									if (uniquePagesTable[i].nameOfIssue != "")
									{
										 data_two = uniquePagesTable[i].nameOfIssue + "\n";
										 datafile_two << data_two;
									}
								}
								else
								{
									if (uniquePagesTable[i].nameOfIssue != "")
									{
										data_one = uniquePagesTable[i].nameOfIssue + "\t" + std::to_string(uniquePagesTable[i].percentageOfReprintedMaterialInIssue) + "\n";
										datafile_one << data_one;
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
									data_two = uniquePagesTable[i].nameOfIssue + "\n";
									datafile_two << data_two;
								}
							}
							else
							{
								data_one = uniquePagesTable[i].nameOfIssue + "\t" + std::to_string(uniquePagesTable[i].percentageOfReprintedMaterialInIssue) + "\n";
								datafile_one << data_one;
							}
						}
					}
				}
			}
		}
	}

	void writeAllFiles(std::string inputlocation, std::string syear, std::string smonth)
	{
		writeComparisonTable(inputFileStructureLocation, stringOfYear, stringOfMonth);
		writeDirectedLinksFiles(inputFileStructureLocation, stringOfYear, stringOfMonth);
		writeMaxMatchList(inputFileStructureLocation, stringOfYear, stringOfMonth);
		writePagePercentageFiles(inputFileStructureLocation, stringOfYear, stringOfMonth);
		writeIssuePercentageFiles(inputFileStructureLocation, stringOfYear, stringOfMonth);
		writeTitlePagePercentageFiles(inputFileStructureLocation, stringOfYear, stringOfMonth);
		writeTitleIssuePercentageFiles(inputFileStructureLocation, stringOfYear, stringOfMonth);
	}
};
