
// note the different names for the C libraries
#include <cstdio>	// cstdio   instead of stdio.h
#include <cstdarg>	// cstdarg  instead of strarg.h
#include <cmath>  	// cmath    instead of math.h

// needed to use some of the math library functions
using namespace std;

// C STRUCT: point

typedef struct pointStruct
{
 //  below of the "fields" of the struct
 int x;
 int y;
} point;

// functions to use the struct point
void init (point* pt1, int px, int py)
{
 pt1->x = px;
 pt1->y = py;
}

double distanceFrom (point pt1, point pt2)
{
  double deltaX = abs ( 1.0 * pt1.x - pt2.x );
  double deltaY = abs ( 1.0 * pt1.y - pt2.y );

  return sqrt ( ( deltaX * deltaX ) + ( deltaY * deltaY ) ); 
}

// note this is unsafe since length of buf is never verified
char*  toStr( point pt, char* buf)
{
 sprintf ( buf, "(%d, %d)", pt.x, pt.y);
 return buf;
} 


int getQuadrant(point pt)
   {
   	if (pt.x > 0 && pt.y > 0)
   	{
   		return 1;
   	}
   	if (pt.x < 0 && pt.y > 0)
   	{
   		return 2;
   	}
   	if (pt.x > 0 && pt.y < 0)
   	{
   		return 4;
   	}
   	if (pt.x < 0 && pt.y < 0)
   	{
   		return 3;
   	}
   	return 0;   	
   } 

// C++ Class - Point2d

class Point2d
{
  // below are the "data members" of the class
  // data members are almost ALWAYS private
  //   data members are also called "instance variable"
  private:
    // the X and Y coordinates for the point
    int x;                        // Line 201
    int y;                        // Line 202


  // Below are the METHODS of the class.
  //
  // Each of these has an implicit/additional "parameter" 
  //  named "this" which is a pointer to the instance of the
  //  class variable listed on the left side of the dot at the
  //  method call
  //
  // Most often METHODS are public
  public:

   // constructors are special forms of METHODS
   // use of class constructors to initialize the variables
   Point2d (int px, int py)
   {
      this->x = px;
      this->y = py;
   }

   // "default" constructor (no parameters) : set point to (0, 0)
   Point2d ( ) 
   {
     this->x = 0;
     this->y = 0;
   }

   void PrintCoordinate(){
    printf("%d\t", this->x );
    printf("%d\n", this->y );
   }

   void setX (int px)
   {
     this->x = px;
   }

   int getX()
   {
     return this->x;
   }

   void setY (int py)
   {
     this->y = py;
   }

   int getY()
   {
     return this->y;
   }

   void setXY (int px, int py)
   {
     this->x = px;
     this->y = py;
   }

   double distanceFrom (Point2d pt)
   {
     double deltaX = abs ( 1.0 * this->x - pt.getX() );
     double deltaY = abs ( 1.0 * this->y - pt.getY() );

     return sqrt ( ( deltaX * deltaX ) + ( deltaY * deltaY ) ); 
   }

   // note this is unsafe since length of buf is never verified
   char*  toStr(char* buf)
   {
    sprintf ( buf, "(%d, %d)", this->x, this->y);
    return buf;
   }  
   
   int getQuadrant()
   {
   	if (this->x > 0 && this->y > 0)
   	{
   		return 1;
   	}
   	if (this->x < 0 && this->y > 0)
   	{
   		return 2;
   	}
   	if (this->x > 0 && this->y < 0)
   	{
   		return 4;
   	}
   	if (this->x < 0 && this->y < 0)
   	{
   		return 3;
   	}
   	return 0;   	
   } 

};


int main ( int argc, char** argv)
{
  //  This is using a "printf" technique that can be nice
  char buffer[100]; // buffer of size 100 to print point/Point2d
 

  // The following code uses the C structure point 

  printf ("Using the C STRUCT point:\n");
  // create a local variable of the point struct to be (0, 0)
  point pt3;
  pt3.x = 0;
  pt3.y = 0;
  printf ("Current pt3: (%d, %d)\n", pt3.x, pt3.y );
  printf ("Current pt3: %s\n", toStr( pt3, buffer) );

  pt3.x = 7; 			// LINE 10
  pt3.y = 2;			// LINE 11
  printf ("Current pt3: %sx", toStr( pt3, buffer) );
   //printf (" exists in Quadrant %d", getQuadrant(pt3) );
  printf ("\n");

  // create a second point
  point pt4;
  init (&pt4, 3, -2);
  printf ("Current pt4: %s\n", toStr( pt4, buffer) );
  printf ("Distance between points %f\n", distanceFrom(pt3, pt4) );
  printf ("Distance between points %f\n", distanceFrom(pt4, pt3) );


  // the following code uses the C++ class Point2d

  printf ("\n\nUsing the C++ CLASS Point2d:\n");
  // create an instance of the Point2d class
  Point2d pt1;  // sets to (0, 0) by default

  // Code to test Access Modifiers - Question 1
   //pt1.x = 1;               // LINE 12
   //pt1.y = 2;               // LINE 13

  printf ("Current pt1: %s\n", pt1.toStr(buffer) );

  // change the point to a different set of coordinates
  pt1.setXY(5, -3);           // LINE 14
  printf ("Current pt1: %s", pt1.toStr(buffer) );

  printf("checking\n");
  pt1.PrintCoordinate(); 
   printf (" exists in Quadrant %d", pt1.getQuadrant( ) );
  printf ("\n");

  Point2d pt2 (3, 7);
  printf ("Current pt2: %s\n", pt2.toStr(buffer) );
  
  // determine the distance between two points
  printf ("Distance between points %f\n", pt1.distanceFrom(pt2) );
  printf ("Distance between points %f\n", pt2.distanceFrom(pt1) );


}



