fullyExtendedModeling: CNFSearchParser.o CNFSearchAlignment.o HHSearchParser.o HHSearchAlignment.o BlastParser.o Parser.o BlastAlignment.o Alignment.o Point.o Target.o Template.o Driver.o
	g++	CNFSearchParser.o CNFSearchAlignment.o HHSearchParser.o HHSearchAlignment.o BlastParser.o Parser.o BlastAlignment.o  Alignment.o  Point.o Target.o Template.o Driver.o -o fullyExtendedModeling


Alignment.o: Alignment.cpp
	g++ -c Alignment.cpp

BlastParser.o: BlastParser.cpp
	g++ -c BlastParser.cpp
	
BlastAlignment.o: BlastAlignment.cpp
	g++ -c BlastAlignment.cpp
	
CNFSearchParser.o: CNFSearchParser.cpp
	g++ -c CNFSearchParser.cpp
	
CNFSearchAlignment.o: CNFSearchAlignment.cpp
	g++ -c CNFSearchAlignment.cpp
	
HHSearchParser.o: HHSearchParser.cpp
	g++ -c HHSearchParser.cpp
	
HHSearchAlignment.o: HHSearchAlignment.cpp
	g++ -c HHSearchAlignment.cpp
		
Parser.o: Parser.cpp
	g++ -c Parser.cpp
	

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