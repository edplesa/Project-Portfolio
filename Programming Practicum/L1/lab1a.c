#include <stdio.h>

void funct1 (int p1, int *p2);

int main()
{
    int x = 7;        
    int y ; 
    int *p;

    printf ("Hello World\n");
    printf ("Print line 0: %d\n", x);

    p = &x; 
    y = *p; 
    *p = x+y ; 

 

    printf ("Print line 1: %d\n", x);
    printf ("Print line 2: %p\n", &x);
    printf ("Print line 3: %d\n", y);
    printf ("Print line 4: %p\n", &y);
    printf ("Print line 5: %p\n", p);
    printf ("Print line 6: %p\n", &p);
    printf ("Print line 7: %d\n", *p);

    // printf ("Print line 8: %d\n", *x); 

    int a = 2;
    int b = 4;
    printf ("Print line 11: For variable a: value: %d, address:  %p\n", a, &a);
    printf ("Print line 12: For variable b: value: %d, address:  %p\n", b, &b);
    funct1 (a, &b);
    printf ("Print line 13: For variable a: value: %d, address:  %p\n", a, &a);
    printf ("Print line 14: For variable b: value: %d, address:  %p\n", b, &b);


}


void funct1 (int p1, int *p2)
{
   printf ("Print line 101: %d\n", p1);
   printf ("Print line 102: %p\n", &p1);
   printf ("Print line 103: %p\n", p2);
   printf ("Print line 104: %p\n", &p2);
   printf ("Print line 105: %d\n", *p2);

   p1 = p1 + 5;
   *p2 = *p2 + 5;
}

