

all: string.o strutil.o main.o string.h strutil.h
	g++ -o exo2 string.o strutil.o main.o

string.o: string.cpp string.h
	g++ -c string.cpp

strutil.o: strutil.cpp strutil.h
	g++ -c strutil.cpp

main.o: main.cpp
	g++ -c main.cpp


clean:
	rm *.o
	rm exo2