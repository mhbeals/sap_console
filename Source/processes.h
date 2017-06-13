#pragma once
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
