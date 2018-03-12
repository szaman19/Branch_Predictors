all: main.o
	g++ main.o -o predictors
main.o: main.cpp
	g++ -g -Wall -std=c++14 main.cpp -c
clean:
	rm *.o *.txt
