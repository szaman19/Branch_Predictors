SOURCE1 = OneBitBimodal
SOURCE2 = TwoBitBimodal
SOURCE3 = GShare
SOURCE4 = Tournament
SOURCE5 = Perceptron

all: main.o
	g++ main.o $(SOURCE1).o $(SOURCE2).o $(SOURCE3).o $(SOURCE4).o -o predictors
main.o: main.cpp $(SOURCE1).o $(SOURCE2).o $(SOURCE3).o $(SOURCE4).o
	g++ -g -Wall -std=c++14 main.cpp -c
$(SOURCE1).o: $(SOURCE1).cpp
	g++ -g -Wall -std=c++14 $(SOURCE1).cpp -c
$(SOURCE3).o: $(SOURCE3).cpp
	g++ -g -Wall -std=c++14 $(SOURCE3).cpp -c
$(SOURCE2).o: $(SOURCE2).cpp
	g++ -g -Wall -std=c++14 $(SOURCE2).cpp -c
$(SOURCE4).o: $(SOURCE4).cpp
	g++ -g -Wall -std=c++14 $(SOURCE4).cpp -c
$(SOURCE5).o: $(SOURCE5).cpp
	g++ -g -Wall -std=c++14 $(SOURCE5).cpp -c
test1: all
	./predictors ../traces/short_trace1.txt short_trace1_output.txt
test2: all
	./predictors ../traces/long_trace1.txt long_trace1_output.txt

ec_driver: PerceptronDriver.cpp
	g++ -g -Wall -std=c++14 PerceptronDriver.cpp -c
ec: $(SOURCE5).o ec_driver
	g++ $(SOURCE5).o PerceptronDriver.o -o PerceptronTest
ec_test:ec
	./PerceptronTest ../traces/short_trace1.txt Perceptron_short_trace1_output.txt

clean:
	rm *.o predictors short_trace1_output.txt long_trace1_output.txt Perceptron_short_trace1_output.txt
