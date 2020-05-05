all: main.cpp
	g++ main.cpp N-Puzzle/N-Puzzle.cpp -o 8-puzzle

clean:
	rm 8-puzzle
