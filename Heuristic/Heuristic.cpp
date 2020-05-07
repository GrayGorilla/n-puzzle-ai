#include "Heuristic.hpp"
#include "../N-Puzzle/N-Puzzle.hpp"
using namespace std;

int UniformCostSearch::heuristicValue(const shared_ptr<State> nextState) {
    return 0;
}

int AStarMisplacedTile::heuristicValue(const shared_ptr<State> nextState) {
    int misplaced = 0;
    Matrix nextMatrix = nextState->getMatrix();
    Matrix goalMatrix = N_Puzzle::convertRawMatrix(GOAL);
    for (int i = 0; i < nextMatrix.size(); i++) {
        for (int j = 0; j < nextMatrix.at(i).size(); j++) {
            if (nextMatrix.at(i).at(j) != goalMatrix.at(i).at(j)) {
                if (nextMatrix.at(i).at(j) == 0) continue;
                else misplaced++;
            }
        }
    }
    return misplaced;
}

int AStarEuclidianDistance::heuristicValue(const shared_ptr<State> nextState) {
    return 2;
}
