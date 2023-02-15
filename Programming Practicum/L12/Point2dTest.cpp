/* Tests for Point2d.cpp using tinytest                     */
/*                                                          */
/* tinytest can be found at:                                */ 
/*     https://github.com/joewalnes/tinytest                */
/*                                                          */
/* Each test is written using the ASSERT_EQUALS( ) macro    */
/*                                                          */
/* ASSERT_EQUALS ( ) takes 2 parameters:		    */
/*  1.  The expected result value			    */
/*  2.  The code to call the functions that SHOULD return   */
/*        the expected result                               */
/*                                                          */
/* For example:                                             */ 
/*  assume we were testing the square root function call    */
/*    of sqrt (25.0)                                        */
/*  which should produce the expected result of: 5.0        */
/*  The ASSERT_EQUALS( ) code should be:                    */
/*    ASSERT_EQUALS ( 5.0, sqrt(25.0) );                    */ 
/*                                                          */
/* TinyTest includes 2 other macros:                        */
/*  1. to test boolean expressions: ASSERT( )               */
/*  2. to test C style strings:     ASSERT_STRING_EQUALS( ) */

// include the TinyTest header file
#include "tinytest.h"

// include the header file for the class to be tested
#include "Point2d.h"

// testing the setX() and getX() methods in class Point2d
void testGetSetX ()
{
  Point2d p1;
  p1.setX(17);
  ASSERT_EQUALS ( 17, p1.getX() );
  p1.setX(-7);
  ASSERT_EQUALS ( -7, p1.getX() );
  p1.setXY ( 9, 1 ); 
  ASSERT_EQUALS (  9, p1.getX() );
}

// testing the setY() and getY() methods in class Point2d
void testGetSetY ()
{
  Point2d p1;
  p1.setY(17);
  ASSERT_EQUALS ( 17, p1.getY() );
  p1.setY(-5);
  ASSERT_EQUALS ( -5, p1.getY() );
  p1.setXY ( 9, 1 ); 
  ASSERT_EQUALS (  1, p1.getY() );
}

// testing the distanceFrom() method in class Point2d
void testDistanceFrom()
{
  Point2d p1 ( 0, 0 );
  Point2d p2 ( 8, 0 );
  // uncomment for an example of a test "failure"
  //ASSERT_EQUALS ( 75.0 , p1.distanceFrom(p2) );
  ASSERT_EQUALS ( 8.0 , p1.distanceFrom(p2) );
  ASSERT_EQUALS ( 8.0 , p2.distanceFrom(p1) );
  p2.setXY ( 3, 4 );
  ASSERT_EQUALS ( 5.0 , p1.distanceFrom(p2) );
  ASSERT_EQUALS ( 5.0 , p2.distanceFrom(p1) );
}

// testing the getQuadrant() method in class Point2d
void testGetQuadrant()
{
  Point2d p1 ( 0, 0 );
  ASSERT_EQUALS ( 0 , p1.getQuadrant() );
  p1.setXY ( 3, 4 );
  ASSERT_EQUALS ( 1 , p1.getQuadrant() );
  p1.setXY ( -3, -4 );
  ASSERT_EQUALS ( 3 , p1.getQuadrant() );
  p1.setXY (-3,5);
  ASSERT_EQUALS (2, p1.getQuadrant());
  //p1.setXY (4,-5);
  //ASSERT_EQUALS (4, p1.getQuadrant());
  p1.setXY (-6,0);
  ASSERT_EQUALS (0, p1.getQuadrant());
}
/* test runner */
int main ( int argc, char** argv )
{
  RUN (testGetSetX);
  RUN (testGetSetY);
  RUN (testDistanceFrom);
  RUN (testGetQuadrant);

  return TEST_REPORT();
}
