all: main.cpp
	g++ main.cpp N-Puzzle/N-Puzzle.cpp State/State.cpp Heuristic/Heuristic.cpp -o 8-puzzle

clean:
	rm 8-puzzle
