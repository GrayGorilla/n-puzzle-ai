#include <chrono>
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
    this->found = false;
    this->totalNodesExpanded = 0;
    this->maxNodesInQueue = 0;
    this->minCost = static_cast<int>INFINITY;
    this->goalMatrix = this->convertRawMatrix(GOAL);
    this->frontier = make_unique<CostPriorityQueue>(StateCompare(true));
    this->frontier->emplace(make_shared<State>(initial, 0));
}

Matrix N_Puzzle::convertRawMatrix(const vector<int> rawMatrix) const {
    int count = 1;
    vector<int> row;
    Matrix newMatrix;

    for (auto val : rawMatrix) {
        row.push_back(val);
        count++;
        if (count % PUZZLE_LENGTH != 1) continue;
        
        newMatrix.push_back(row);
        row.clear();
    }
    return newMatrix;
}

void N_Puzzle::solve() {
    int currentCost, heuristicVal;
    auto startTime = chrono::high_resolution_clock::now();
    // Get initial state
    this->currentState = this->frontier->top();
    this->frontier->pop();
    // Print initial state
    cout << "\nExpanding initial state:" << endl;
    this->currentState->printMatrix();

    // Expand nodes until optimal path is found
    while (true) {
        // Goal state reached
        if (this->currentState->getMatrix() == this->goalMatrix) {
            currentCost = this->currentState->getCost();
            // Update min moves
            if (currentCost < this->minCost) {
                // First solution found
                if (! this->found) {
                    cout << "First solution found !" << endl << endl;
                    this->found = true;
                // Better solution found
                } else {
                    cout << "More optimal solution found !" << endl << endl;
                }
                this->solvedState = this->currentState;
                this->minCost = currentCost;
            // Lesser solution found
            } else {
                cout << "Solution found." << endl << endl;
            }
        // Not goal, expand current node (unless pruned)
        } else if (! this->found || this->currentState->getCost() < this->minCost) {
            this->makeMoves();
            this->totalNodesExpanded++;
        }
        // Optimal solution locked in
        if (this->frontier->empty()) {
            auto endTime = chrono::high_resolution_clock::now();
            auto time = endTime - startTime;
            this->recordTime = time / chrono::milliseconds(1);
            cout << "Solved !!!" << endl << endl;
            this->printResults();
            break;
        }
        // Pop node off the queue => make it new current node
        this->currentState = this->frontier->top();
        this->frontier->pop();
        // Display trace if not prunned
        if (this->currentState->getCost() < this->minCost) {
            heuristicVal = 0;       // todo: call heuristic function !!
            currentCost = this->currentState->getCost() - heuristicVal;
            cout << "The best state to expand with g(n) = " << currentCost
                << " & h(n) = " << heuristicVal << " is:" << endl;
            this->currentState->printMatrix();
            cout << "Expanding node..." << endl << endl;
        }
    }
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
    // Record largest queue
    if (this->frontier->size() > this->maxNodesInQueue) {
        this->maxNodesInQueue = this->frontier->size();
    }
}

void N_Puzzle::printResults() {
    cout << "To solve this puzzle, the search algorithm expanded a total of "
         << this->totalNodesExpanded << " node(s)." << endl;
    cout << "The maximum number of nodes in the queue at any one time: " 
         << this->maxNodesInQueue << '.' << endl;
    cout << "This puzzle was solved optimally in " << this->minCost <<" move(s) "
         << "& it took " << this->recordTime << " ms." << endl << endl;
}

N_Puzzle::~N_Puzzle() { cout << "<N-Puzzle de-alocated>" << endl; }
