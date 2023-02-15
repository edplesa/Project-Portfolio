#include <cstdio>
#include <cstdlib>
#include <ctime>

// using Pass-by-Value
void passBV ( int v1 )
{
  // do something
  v1++;
  printf ("PBV Param: %d\n", v1);
}

// using Pass-by-Address
void passBA ( int* v1)
{
  // do something
  (*v1)++;
  printf ("PBA Param: %d\n", *v1);
}

// using Pass-by-Reference
void passBR ( int& v1 )
{
  // do something
  v1++;
  printf ("PBR Param: %d\n", v1);
}

// using Pass-by-Constant-Reference
void passBCR ( const int& v1 )
{
  // do something
  //v1++;
  printf ("PBCR Param: %d\n", v1);
}

int main (int argc, char** argv)
{
 int number = 10;

 printf ("Initial value number: %d\n\n", number);

 printf ("Before passBV  number: %d\n", number);
 passBV  (  number );      // using Pass-by-Value
 printf ("After passBV  number: %d\n\n", number);

 number = 10;
 printf ("Before passBA  number: %d\n", number);
 passBA  ( &number );      // using Pass-by-Address
 printf ("After passBA  number: %d\n\n", number);

 number = 10;
 printf ("Before passBR  number: %d\n", number);
 passBR  (  number );      // using Pass-by-Reference
 printf ("After passBR  number: %d\n\n", number);

 number = 10;
 printf ("Before passBCR  number: %d\n", number);
 passBCR (  number );      // using Pass-by-Constant-Reference
 printf ("After passBCR number: %d\n\n", number);

 return 1;
}
