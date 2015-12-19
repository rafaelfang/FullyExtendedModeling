fullyExtendedModeling:  Alignment.o Point.o Target.o Template.o Driver.o
	g++     Alignment.o  Point.o Target.o Template.o Driver.o -o fullyExtendedModeling


Alignment.o: Alignment.cpp
	g++ -c Alignment.cpp


	

Point.o:Point.cpp
	g++ -c Point.cpp
	
Target.o: Target.cpp
	g++ -c Target.cpp
	
Template.o: Template.cpp
	g++ -c Template.cpp
	
Driver.o: Driver.cpp
	g++ -c Driver.cpp
	

clean:
	rm *.o fullyExtendedModeling