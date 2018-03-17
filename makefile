SOURCE1 = OneBitBimodal
SOURCE2 = TwoBitBimodal
SOURCE3 = GShare
SOURCE4 = Tournament

all: main.o
	g++ main.o perceptron.o $(SOURCE1).o $(SOURCE2).o $(SOURCE3).o $(SOURCE4).o -o predictors
main.o: main.cpp perceptron.cpp $(SOURCE1).o $(SOURCE2).o $(SOURCE3).o $(SOURCE4).o
	g++ -g -Wall -std=c++14 main.cpp perceptron.cpp -c
$(SOURCE1).o:
	g++ -g -Wall -std=c++14 $(SOURCE1).cpp -c



$(SOURCE3).o:
	g++ -g -Wall -std=c++14 $(SOURCE3).cpp -c
$(SOURCE2).o:
	g++ -g -Wall -std=c++14 $(SOURCE2).cpp -c

$(SOURCE4).o:
	g++ -g -Wall -std=c++14 $(SOURCE4).cpp -c
clean:
	rm *.o *.txt
