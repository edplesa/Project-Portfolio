
/**  This code will represent line segments in a 2-D space.
  * 
  * This code will use the Point2d.cpp code
  *    Note that the Point2d class uses integer values for the X and Y corrdinates
  * 
  * The code is attempting to show how one class might use/contain another class
  *   This is often referred to as "aggregation", "composition"
  *   or having a "HAS-A" relationship.
  * 
  * So the Segment class "has a" member of the Point2D class (actually it has 2).
  */

#include "Point2d.h"

// C style constant (sometimes called a "magic number")
#define MAX 1000    

// C++ style constant
const double PI = 3.14159265359;

class Segment
{
 private:
   Point2d endp1;
   Point2d endp2;

 public:
   Segment();
   Segment ( Point2d p1, Point2d p2 );
   void changeEndPoint1 ( Point2d p);
   void changeEndPoint2 ( Point2d p);

   // the following "const" methods don't try to change the
   //  data members in the instance of the class
   // const is actually modifying the this pointer
   double length() const;
   double slope() const;
   char* toStr (char* buf) const;
   double calcAngleOfIntersection(const Segment &s2);
};


  Segment::Segment()
  {
   printf ("In constructor Segment()\n");
   endp1.setXY( 0, 0 );
   endp2.setXY( 0, 0 );
  }

  Segment::Segment ( Point2d p1, Point2d p2 ):endp1(p1),endp2(p2)
  {
   printf ("In constructor Segment(Point2d, Point2d)\n");   
  }

  void Segment::changeEndPoint1 ( Point2d p)
  {
   endp1 = p;
  }

  void Segment::changeEndPoint2 ( Point2d p)
  {
   endp2 = p;
  }


  double Segment::length() const
  {
  	return endp2.distanceFrom(endp1);
  }

  double Segment::slope() const
  {
  	if (endp2.getX() == endp1.getX()) {
  		return INFINITY;
  	}
  	return ((endp2.getY() - endp1.getY()) / (endp2.getX() - endp1.getX()));     
  }

  // note this is unsafe since length of buf is never verified
  char* Segment::toStr (char* buf) const
  {
    char tbuf1[300], tbuf2[300];
    sprintf ( buf, "End Point 1: %s, End Point 2: %s", 
               endp1.toStr(tbuf1), endp2.toStr(tbuf2) );

    return buf;
   }

// calculate the Angle of Intersection of the two lines
// that would contain the two given segments
double Segment::calcAngleOfIntersection (const Segment &s2)
{
 double m1 = this->slope();
 double m2 = s2.slope();

 // note atan() return radians, so convert to degrees
 //  The angle returned is from positive x axis
 double angle1 = atan( m1 ) * 180.0 / PI ;
 double angle2 = atan( m2 ) * 180.0 / PI ;

 // note use abs( ) if you only want positive angle values
 return angle1 - angle2;
}

// calculate the Y Intercept of the line that would 
//   contain the given segment
double yintercept ( Segment s1 )
{
 double m1 = s1.slope();

}

int main (int argc, char** argv)
{
 printf ("Value of PI: %f\n", PI);
 //PI = 2.71828;
 printf ("Value of PI: %f\n\n", PI);

 char buffer[100];

 Point2d p1 (3, 5);
 Point2d p2 (-4, 2);
 
 printf ("\nCreating Segments\n"); 
 Segment seg1 ( p1, p2);
 Segment seg2;
 printf ("Segment1: %s\n", seg1.toStr(buffer) );
 printf ("Segment2: %s\n", seg2.toStr(buffer) );

 printf ("\nChanging Segments\n"); 
 p2.setXY ( 7, -4 );
 printf ("Segment1: %s\n", seg1.toStr(buffer) );

 seg1.changeEndPoint2 ( p2 );
 printf ("Segment1: %s\n", seg1.toStr(buffer) );
 seg1.changeEndPoint2 ( Point2d( -4, 12) );
 printf ("Segment1: %s\n", seg1.toStr(buffer) );

 printf ("\nInformation On Segments\n"); 
 printf ("Length of Segement1: %f\n", seg1.length() );
 printf ("Slope of Segement1: %f\n", seg1.slope() );
 printf ("Slope of Segement2: %f\n", seg2.slope() );

 double angle;
 // calling calcAngleOfIntersection( ) as a function
 //angle = calcAngleOfIntersection ( seg1, seg2 );
 // calling calcAngleOfIntersection( ) as a method
  angle =  seg1.calcAngleOfIntersection ( seg2 );
 printf ("Angle of Intersection: %f\n\n", angle );

 printf ("Sizeof Segment: %d\n", sizeof (Segment) );
 printf ("Sizeof Segment pointer: %d\n", sizeof(Segment*) );
 return 1;
}

