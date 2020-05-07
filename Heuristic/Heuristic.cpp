#include <cmath>
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
    int x, y, val, totalEuclid = 0;
    Matrix nextMatrix = nextState->getMatrix();
    Matrix goalMatrix = N_Puzzle::convertRawMatrix(GOAL);

    for (val = 1; val <= PUZZLE; val++) {
        for (int i = 0; i < nextMatrix.size(); i++) {
            for (int j = 0; j < nextMatrix.at(i).size(); j++) {
                if (val == nextMatrix.at(i).at(j)) {
                    y = i;
                    x = j;
                }
            }
        }
        for (int i = 0; i < goalMatrix.size(); i++) {
            for (int j = 0; j < goalMatrix.size(); j++) {
                if (val == goalMatrix.at(i).at(j)) {
                    y = abs(y - i);
                    x = abs(x - j);
                }
            }
        }
        totalEuclid += sqrt(pow(x, 2) + pow(y, 2));
    }

    return totalEuclid;
}
