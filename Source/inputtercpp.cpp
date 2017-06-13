#include "stdafx.h"
#include "coresettings.h"

// Input Functions
void makeCFTable(string inputlocation, string syear, string smonth, string syear_1, string smonth_1)
{
	int cfpm; // perfect match value
	int cflm; // lefthand match value
	int cfrm; // righthand match value
	string cfleft; // path to left file
	string cfright; // path to right file
	cfvalues empty;
	ifstream Data(inputlocation + "\\inputs\\rawmatchingreports\\" + syear_1 + "_" + smonth_1 + ".txt");
	ifstream Data2(inputlocation + "\\inputs\\rawmatchingreports\\" + syear + "_" + smonth + ".txt");
	int i = -1;

	while (Data >> cfpm >> cflm >> cfrm >> cfleft >> cfright)
	{
		i += 1;
		cftable.push_back(empty);
		cftable[i].cfpm = cfpm;
		cftable[i].cflm = cflm;
		cftable[i].cfrm = cfrm;
		cftable[i].cfam = (cflm + cfrm) / 2;
		cftable[i].cfleft = cfleft;
		cftable[i].cfright = cfright;
	}

	while (Data2 >> cfpm >> cflm >> cfrm >> cfleft >> cfright)
	{
		i += 1;
		cftable.push_back(empty);
		cftable[i].cfpm = cfpm;
		cftable[i].cflm = cflm;
		cftable[i].cfrm = cfrm;
		cftable[i].cfam = (cflm + cfrm) / 2;
		cftable[i].cfleft = cfleft;
		cftable[i].cfright = cfright;
	}
}
void makeBLTable(string inputlocation, string syear, string smonth, string syear2, string smonth2, string syear_1, string smonth_1)
{
	blcounts empty;
	ifstream Data_1(inputlocation + "\\inputs\\bltables\\" + syear_1 + "_" + smonth_1 + ".tsv");
	ifstream Data(inputlocation + "\\inputs\\bltables\\" + syear + "_" + smonth + ".tsv");
	ifstream Data2(inputlocation + "\\inputs\\bltables\\" + syear2 + "_" + smonth2 + ".tsv");
	string uid;
	double wc;
	string iid;
	double iwc;
	int i = -1;
	while (Data_1 >> uid >> wc >> iid >> iwc)
	{
		i += 1;
		bltable.push_back(empty);
		bltable[i].bluid = uid;
		bltable[i].blwc = wc;
		bltable[i].blissue = iid;
		bltable[i].blissuewc = iwc;
	}

	while (Data >> uid >> wc >> iid >> iwc)
	{
		i += 1;
		bltable.push_back(empty);
		bltable[i].bluid = uid;
		bltable[i].blwc = wc;
		bltable[i].blissue = iid;
		bltable[i].blissuewc = iwc;
	}

	while (Data2 >> uid >> wc >> iid >> iwc)
	{
		i += 1;
		bltable.push_back(empty);
		bltable[i].bluid = uid;
		bltable[i].blwc = wc;
		bltable[i].blissue = iid;
		bltable[i].blissuewc = iwc;
	}

}
void makeNTTable(string inputlocation)
{
	ifstream data(inputlocation + "\\inputs\\NormalisedTitlesns.tsv");
	string title = "";
	string ntitle = "";
	normTitle empty;
	int i = -1;

	while (data >> title >> ntitle)
	{
		i += 1;
		normTitles.push_back(empty);
		normTitles[i].title = title;
		normTitles[i].ntitle = ntitle;
	}
}
