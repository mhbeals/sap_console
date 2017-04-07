#pragma once
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
