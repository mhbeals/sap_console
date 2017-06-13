#pragma once

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>
#include <ostream>
#include <istream>
#include <algorithm>
using namespace std;

struct copyfindEntry {
	int copyfindPerfectMatch; // pull from copyfind file
	int copyfindLefthandMatch; // pull from copyfind file
	int copyfindRighthandMatch; // pull from copyfind file
	int copyfindAverageMatch; // process in makeCFTable
	int copyfindMaximumWordCount; // process in processMaximumValues
	double fullPageWordCountOfLeftPage; // pull from wordCountTable
	string issueNameofLeftPage; // pull from wordCountTable
	int copyfindCombinedAverageWordCountForLeftIssue; // process in processMaximumValues
	double copyfindFullWordCountOfLeftIssue; // pull from BL table
	string copyfindPathOfLeftFile; // pull from copyfind file
	string copyfindPathOfRightFile; // pull from copyfind file
	int yearOfLeftPage; // process in makeCFTable
	int monthOfLeftPage; // process in makeCFTable
	int dayOfLeftPage; // process in makeCFTable
	string titleOfLeftPage; // process in makeCFTable
	string pageNumberOfLeftPage; // process in makeCFTable
	string nameOfLeftPage; // pull from file
	string normalisedNameOfLeftPage; // processed from file
	int yearOfRightPage; // process in makeCFTable
	int monthOfRightPage; // process in makeCFTable
	int dayOfRightPage; // process in makeCFTable
	string titleOfRightPage; // process in makeCFTable
	string pageOfRightPage; // process in makeCFTable
	string nameOfRightPage; // pull from file
	string normalisedNameOfRightPage; // normalised unique id of righthand file; processed from file
};
struct wordCountTableEntry {
	string wordCountTablePageName; // full page id; pull from file
	double wordCountTableWordCountOfPage;  // full page wc; pull from file
	string wordCountTableIssueName; // full page issue; pull from file
	double wordCountTableFullWordCountOfIssue; // full issue wc; pull from file
};
struct normalisedTitleReference {
	string title; // BL title
	string normalisedTitle; // Normalised title
};

struct articleEntry //list all unique articles present in the input data
{
	string normalisedNameOfPage; // pull from copyfind table
	string nameOfPage; // pull from copyfind table
	string titleOfPage; // pull from copyfind table
	int yearOfPage; // pull from copyfind table
	int monthOfPage; // pull from copyfind table
	int dayOfPage;  // pull from copyfind table
	string pageNumberOfPage;  // pull from copyfind table
};
struct comparisonEntry // displays a pair of pages that has been compared
{
	int perfectMatchOfComparison;  // pull from copyfind table
	int leftHandMatchOfComparison;  // pull from copyfind table
	int rightHandMatchOfComparison;  // pull from copyfind table
	articleEntry laterPage; // data from copyfind table
	articleEntry earlierPage; // data  from copyfind table
};
struct uniquePageEntry //final manifest; contains each target only once
{
	string nameOfLaterPage;  // pull from copyfind table
	string nameOfEarlierPage;   // pull from copyfind table
	bool bHasDescendents;   // pull from copyfind table
	bool bHasNoDescendents;   // pull from copyfind table
	double maximumAverageWordCountForReprintsOnLaterPage; // (reprints) maximum average word count of target page; pull from cftable
	double fullWordCountofLaterPage; // (whole) full-page word count of target page; pull from cftable via wordCountTable
	string nameOfIssue; // issue of target article; pull from cftable
	double combinedAverageWordCountForIssue; // (reprints) maximum average word count of target issue; pull from cftable
	double fullWordCountOfIssue; // (whole) full-issue word count of targe page; pull from cftable 
	double percentageOfReprintedMaterialOnPage; // maximum average word count-to-page ratio; process in results
	double percentageOfReprintedMaterialInIssue; // all maximum average word counts-to-issue ratio; process in results
};

extern vector<copyfindEntry> copyfindTable; //vector for raw Copyfind data
extern vector<wordCountTableEntry> wordCountTable; //vector for British Library wordcount data
extern vector<normalisedTitleReference> normalisedTitlesTable; //vector for normalised titles
extern vector<comparisonEntry> comparisonsTable; //vector for comparison calculations
extern vector<uniquePageEntry> uniquePagesTable; // vector of unique pages
