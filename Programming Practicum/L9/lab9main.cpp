#include "Date.h"

/*Task 7 - Complete the changeDatePBV and changeDatePBA*/

// attempt to change the date instance using a Pass-By-Value parameter
void changeDatePBV(Date d)
{
    d.setDay(6);
    d.setMonth(6);
    d.setYear(6);
}

// attempt to change the date instance using a Pass-By-ADDRESS parameter
void changeDatePBA(Date* d)
{
    d->setMonth(12);
    d->setDay(25);
}

// This function uses the C++ TRUE Pass-by-Reference parameter syntax
// attempt to change the date instance using a Pass-By-REFERENCE parameter
void changeDatePBR(Date& d)
{
    d.setMonth(12);  // no referencing or dereferencing required!
    d.setDay(25);
}

int main(int argc, char** argv)
{
    char buffer[100];   // buffer of size 100 to print dates

    // create a new instance of the Date class
    Date d; //  the default constructor is called 
    printf("Default date: %s\n", d.toStr(buffer));

    Date d2; //  the default constructor is called
    d2.setMonth(10);
    d2.setDay(31);
    d2.setYear(20);
    printf("Happy Halloween: %s\n", d2.toStr(buffer));

    // create an instance of Date using the constructor with
    //   three parameters

    Date d3(05, 05, 20);
    printf("Last day for CS 211: %s\n", d3.toStr(buffer));


    // Why do CS majors get Halloween and Christmas confused?
    d2.setMonth(10);
    d2.setDay(31);
    d2.setYear(20);
    printf("Happy Halloween: %s\n", d2.toStr(buffer));
    changeDatePBV(d2);
    printf("PBV Attempt - Merry Christmas?: %s\n", d2.toStr(buffer));

    d2.setMonth(10);
    d2.setDay(31);
    d2.setYear(20);
    printf("Happy Halloween: %s\n", d2.toStr(buffer));
    changeDatePBA(&d2);
    printf("PBA Attempt - Merry Christmas?: %s\n", d2.toStr(buffer));

    d2.setMonth(10);
    d2.setDay(31);
    d2.setYear(20);
    printf("Happy Halloween: %s\n", d2.toStr(buffer));
    changeDatePBR(d2);
    printf("PBR Attempt - Merry Christmas?: %s\n", d2.toStr(buffer));

    Date d4(12, 25, 2020);


    if (d2.sameDay(d4)) {
        printf("Merry Christmas\n");
    }


    return 1;
}
