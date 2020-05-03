all: main.cpp
	g++ main.cpp EightPuzzle/EightPuzzle.cpp -o 8-puzzle

clean:
	rm 8-puzzle
