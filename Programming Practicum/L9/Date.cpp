#include "Date.h"

// This class does not have any real constructors (yet)
/*Task 1 - Complete the default constructor,
  Date() will set the date to January 1st, 2000*/
Date::Date()
{
    month = 1;
    day = 1;
    year = 2000;
}

/*Task 2 - Complete the constructor below*/

Date::Date(int month, int day, int year) {
    this->month = month;
    this->day = day;
    this->year = year;
}

//Getters

int Date::getDay() {
    return day;
}

/*Task 3: Part a - Complete the getters below*/
int Date::getMonth() {
    return this->month;
}
int Date::getYear() {
    return this->year;
}

//Setters

void Date::setDay(int d)
{
    static int MaxDayCount[] = { 0, 31, 28, 31, 30, 31, 30,
      31, 31, 30, 31, 30, 31 };

    if (month >= 1 && month <= 12 && d >= 1 &&
        d <= MaxDayCount[month])
        day = d;
    else
        day = 1;
}

/*Task 3 - Complete the setters below*/


/*Task 4 - Ensure setMonth is only setting
  valid values for month (1 - 12)*/
void Date::setMonth(int m)
{
    if (m >= 1 && m <= 12)
        month = m;
    else
        month = 1;
}

/*Task 5 - Ensure setYear is only setting
  valid values for year (2000 - 2020). If the
  passed parameter is XX (two digit value) store
  it as 20XX
  Example: if y = 20
           then year = 2020
 */

void Date::setYear(int y)
{
    if ((y >= 2000 && y <= 2020))
    {
        year = y;
    }
    else if ((y >= 0 && y <= 20))
    {
        year = 2000 + y;
    }
    else
    {
        year = 2000;
    }
}


/*Task 6 - Complete the sameDay function that
  compares two Dates and returns true if they
  are the same*/
bool Date::sameDay(Date d2) {
    if (this->day == d2.day)
    {
        return true;
    }
    return false;
}


// note this is unsafe since length of buf is never verified
char* Date::toStr(char* buf)
{
    static char* Months[] = { "NoMonth",
       "January",   "February", "March",    "April",
       "May",       "June",     "July",     "August",
       "September", "October",  "November", "December" };

    // for MDY format
    //sprintf ( buf, "%s %d, %d", Months[month], day, year );

    // for mm/DD/YYYY format
    sprintf(buf, "%02d/%02d/%d", month, day, year);

    return buf;
}



