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
    this->solved = false;
    this->goalState = make_shared<State>(GOAL, -1);
    this->frontier = make_unique<CostQueue>(StateCompare(true));
    this->frontier->emplace(make_shared<State>(initial, 0));
}

void N_Puzzle::solve() {
    int currentCost, heuristicVal;
    // Get initial state
    this->currentState = this->frontier->top();
    this->frontier->pop();
    
    // Print initial state
    cout << "Expanding initial state:" << endl;
    this->currentState->printMatrix();

    // todo: don't let function break out right after finding goal !!!
    // Expand nodes until optimal path is found
    while (! this->solved) {
        // Goal state reached
        if (this->currentState->getMatrix() == this->goalState->getMatrix()) {
            cout << "Solved !!!" << endl << endl << endl;
            this->solved = true;
            break;
        }
        // Expand current node and select new current
        this->makeMoves();
        this->currentState = this->frontier->top();
        this->frontier->pop();

        heuristicVal = 0;       // todo: call heuristic function !!
        currentCost = this->currentState->getCost() - heuristicVal;
        cout << "The best state to expand with g(n) = " << currentCost
             << " & h(n) = " << heuristicVal << " is:" << endl;
        this->currentState->printMatrix();
        cout << "Expanding..." << endl << endl;
    }
    return;
}

void N_Puzzle::makeMoves() {
    shared_ptr<State> currentMove;
    int currentCost = this->currentState->getCost();    // g(n)
    int heuristicVal = 0;                               // h(n)     // todo: call heuristic function !!
    for (int move = UP; move <= RIGHT; move++) {
        currentMove = this->currentState->makeMove(static_cast<Direction>(move));
        // Only access legal moves
        if (currentMove) {
            currentMove->setCost(currentCost + 1 + heuristicVal);
            this->frontier->push(currentMove);
        }
    }
}

N_Puzzle::~N_Puzzle() { cout << "<N-Puzzle dealocated>" << endl; }
