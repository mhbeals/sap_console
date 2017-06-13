#pragma once
<<<<<<< HEAD
#include "coresettings.h"

void makeComparisonsTable();
void clearVectors();
void processDirectLinkComparisons();
void crossReferenceValuesInWordCountAndCopyfindTables();
void regexCopyfindTableTitles();
void assignMaximumAverageWordCountValues();
void writeComparisonTable(string inputlocation, string syear, string smonth);
void writeDirectedLinksFiles(string inputlocation, string syear, string smonth);
void writeMaxMatchList(string inputlocation, string syear, string smonth);
void writePagePercentageFiles(string inputlocation, string syear, string smonth);
void writeIssuePercentageFiles(string inputlocation, string syear, string smonth);
void writeTitleIssuePercentageFiles(string inputlocation, string syear, string smonth);
void writeTitlePagePercentageFiles(string inputlocation, string syear, string smonth);
=======
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>
#include <ostream>
#include <istream>
using namespace std;

void makeCFTable(string inputlocation, string syear, string smonth);
void makeBLTable(string inputlocation, string syear, string smonth, string syear2, string smonth2);
void makeNTTable(string inputlocation);
void makecomparisonsTable();
void clearVectors();
void processDLcomparisons();
void crossReferenceValues();
void regexCopyfind();
void crossReferenceValues();
void processMaximumValues();
void writeComparisonTable(string inputlocation, string syear, string smonth);
void writeDirectedLinksTables(string inputlocation, string syear, string smonth);
void writeMaxMatchList(string inputlocation, string syear, string smonth);
void writePagePercentage(string inputlocation, string syear, string smonth);
void writeIssuePercentage(string inputlocation, string syear, string smonth);
void writeTitleIssuePercentage(string inputlocation, string syear, string smonth);
void writeTitlePagePercentage(string inputlocation, string syear, string smonth);
>>>>>>> origin/master
