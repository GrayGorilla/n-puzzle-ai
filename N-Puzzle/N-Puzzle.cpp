#include <ctime>
#include <cmath>
#include "N-Puzzle.hpp"
using namespace std;

N_Puzzle::N_Puzzle(const vector<int> initial) {
    int puzzLength = sqrt(PUZZLE + 1);
    vector<int> rawMatrix;
    srand(time(nullptr));

    // Exit if puzzle type invalid
    if (puzzLength != floor(puzzLength)) {
        cerr << "Puzzle type is not valid.  Exiting program." << endl;
        exit(1);
    }

    // Set current & goal states
    this->currentState = make_shared<State>(initial, 0);
    this->goalState = make_shared<State>(GOAL, -1);

    this->currentState->printMatrix();
    this->goalState->printMatrix();
}

int N_Puzzle::solve() {
    // todo: Set frontier(StateCompare(true)) before pushing initial state
    cout << "Write code to solve this puzzle!" << endl;
}

N_Puzzle::~N_Puzzle() { cout << "N-Puzzle dealocated." << endl; }
