all: main.o
	g++ main.o -o predictors
main.o: main.cpp
	g++ -g -Wall main.cpp -c
clean:
	rm *.o output.txt
