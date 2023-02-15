#include <cstdio>
#include <cstdlib>


class Date
{
private:
    int month;
    int day;
    int year;

public:
    Date();
    Date(int month, int day, int year);
    char* toStr(char* buf);
    int getDay();
    int getMonth();
    int getYear();
    void setDay(int d);
    void setMonth(int m);
    void setYear(int y);
    bool sameDay(Date d2);

};


