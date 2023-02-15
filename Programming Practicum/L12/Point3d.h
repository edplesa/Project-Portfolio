// use the #ifndef to stop any redeclaration of the Point3d class
#ifndef POINT3D_CLASS
#define POINT3D_CLASS

#include "Point2d.h"

// The class Point3d inherits from the class Point2d
//   Data Members and Methods that exist in Point2d automatically
//   exist in the class Point3d

class Point3d : public Point2d
// The above: ^^^^^^^^^^^^^^^^ specifies the inheritance relationship
{
 private:
   // Only need to specify the data member for the Z coordinate 
   //    since the X and Y coordinates are inherited
   int z;

 public:
   Point3d (int px, int py, int pz);
   Point3d ();

   void setZ (int pz);
   int getZ() const;

   void setXYZ ( int px, int py, int pz);
   double distanceFrom (Point3d pt) const;
   char* toStr(char* buf) const;
}; 

#endif
