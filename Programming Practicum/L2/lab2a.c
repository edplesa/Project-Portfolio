#include <stdio.h>
#include <stdlib.h>


void printFunction(int *p){

  printf("%d\n",*p );
}



int main (int argc, char** argv)
{
  /* Question 1 */
  int a = 10; 
  int b = 20; 
  int *ptr = &b; 

  printFunction(&a);
 
  // Passing b to printFunction

  

  /* Question 2 and 3 */
  int var1[20];
  int *var2;

  printf ("Sizeof var1: %d\n", sizeof (var1));
  printf ("Sizeof var2: %d\n", sizeof (var2));

  /* Question 4 */
  printf ("Value of var1: %d\n", var1);
  printf ("Address of var1: %d\n", &var1);
  printf ("Address of var1[0]: %d\n", &var1[0]);
  var1[0] = 1;

  printf ("Value of var2: %d\n", var2);
  printf ("Address of var2: %d\n", &var2);
  printf ("Address of var2[0]: %d\n", &var2[0]);
  //var2[0] = 2;


  /* Questions 5 and 6 */
  int arr1[10];
  int arr2[10];
  int arr3[10];
  int i;

  for (i = 0 ; i < 10 ; i++)
    {
     arr1[i] = 100 + i;
     arr3[i] = 300 + i;
    }

  for (i = 0 ; i < 15 ; i++)
    {
     arr2[i] = 200 + i;
    }

  printf ("arr1: ");
  for (i = 0 ; i < 10 ; i++)
    printf ("%d, ", arr1[i]);
  printf ("\n");

  printf ("arr2: ");
  for (i = 0 ; i < 10 ; i++)
    printf ("%d, ", arr2[i]);
  printf ("\n");

  printf ("arr3: ");
  for (i = 0 ; i < 10 ; i++)
    printf ("%d, ", arr3[i]);
  printf ("\n");


  return 0;
}

