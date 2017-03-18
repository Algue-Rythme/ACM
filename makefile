FLAGS=-std=c++11 -s -O2 -Wall -pedantic

all:
	g++ $(FLAGS) louisB_$(NUM).cpp

test:
	g++ $(FLAGS) test_generator_$(NUM).cpp -o create
