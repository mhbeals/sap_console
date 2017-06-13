#include <string>
using namespace std;

string getMonth(int month);

bool isLeapYear(int year);

int monthToDays(int month, bool isLeapYear);

int dayOfWeek(int year, int month, int day);

int findDaysBetweenWithSameYears(int i);

int findDaysBetweenWithDifferentYears(int i);