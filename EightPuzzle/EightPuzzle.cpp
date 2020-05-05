#include <iostream>
#include <ctime>
#include <cmath>
#include "N-Puzzle.hpp"
using namespace std;

N_Puzzle::N_Puzzle() {
    int puzzLength = sqrt(PUZZLE + 1);
    vector<int> rawMatrix;
    srand(time(nullptr));

    // Exit if puzzle type invalid
    if (puzzLength != floor(puzzLength)) {
        cerr << "Puzzle type is not valid.  Exiting program." << endl;
        exit(1);
    }

    // Set goal state
    for (int val = 1; val <= pow(puzzLength, 2); val++) {
        if (val == pow(puzzLength, 2)) {
            rawMatrix.push_back(val);
        } else {
            rawMatrix.push_back(val);
        }
    }

    this->goalState.setMatrix(rawMatrix, 0);
    this->goalState.printMatrix();
}

vector<int> randomPuzzle() {
    return vector<int>();
}

int N_Puzzle::solve() {
    cout << "Write code to solve this puzzle!" << endl;
}

N_Puzzle::~N_Puzzle() { cout << "N-Puzzle dealocated" << endl; }
