lab10b: lab10b.o Point2d.o
	g++ -o lab10b lab10b.o Point2d.o

lab10b.o: lab10b.cpp Point2d.h
	g++ -c lab10b.cpp

Point2d.o: Point2d.cpp Point2d.h
	g++ -c Point2d.cpp

clean:
	rm lab10b.o Point2d.o lab10b
