# This line is a comment
#
# This makefile can produce 2 different executables: lab11 & Point2dTest
#
#   The assumption is that:
#      - the "Production Executable" is: lab11 
#      - the "Testing Executable" is:    Point2dTest
#
# Below is the rule/target to create the "Production Executable"
#  This could be created by typing:
#    make
#    make lab11
#    make all 
lab12: lab12.o Point3d.o Point2d.o 
	g++ -o lab12 lab12.o Point3d.o Point2d.o 

# Below is the rule/target for "make all"
all: lab12 Point2dTest

# Below is the rule/target to create the "Testing Executable"
#  This could be created by typing:
#    make Point2dTest
#    make all
# 
# Note: this rule does not create an object ".o" file for the "Test Code"
#   This goes against most ideas of "separate compilation"
#   However, this is somewhat "common practice" for Testing Code
Point2dTest: Point2d.o Point2dTest.cpp
	g++ -o Point2dTest Point2d.o Point2dTest.cpp

# rule to create the object file for the "Production Code"
lab12.o: lab12.cpp Point2d.h Point3d.h
	g++ -c lab12.cpp

# rule to create the object file for the "Point2d Class"
Point2d.o: Point2d.cpp Point2d.h
	g++ -c Point2d.cpp

# rule to create the object file for the "Point3d Class"
Point3d.o: Point3d.cpp Point3d.h
	g++ -c Point3d.cpp
# rule to remove the executables and object files created by this makefile
#  use so that a subsequent use a "make all" will produce a "clean" version
clean:
	rm lab12.o Point2d.o Point3d.o lab12 Point2dTest
