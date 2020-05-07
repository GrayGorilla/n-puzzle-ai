#include <chrono>
#include <stack>
#include <cmath>
#include "N-Puzzle.hpp"
using namespace std;

/* Constructor */

N_Puzzle::N_Puzzle(const vector<int> initial) {
    int puzzLength = sqrt(PUZZLE + 1);

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
    this->goalMatrix = N_Puzzle::convertRawMatrix(GOAL);
    this->frontier = make_unique<CostPriorityQueue>(StateCompare(true));
    this->frontier->emplace(make_shared<State>(initial));
}

/* Mutators */

void N_Puzzle::solve() {
    int distance, heuristicVal, costEst;
    string stateStr;
    auto startTime = chrono::high_resolution_clock::now();
    // Get heuristic
    this->heuristic = make_unique<UniformCostSearch>();
    // Get initial state
    this->currentState = this->frontier->top();
    this->frontier->pop();
    // Mark as visited node
    this->visitedNodes.insert(N_Puzzle::matrixToString(this->currentState->getMatrix()));
    // Print initial state
    cout << "\nExpanding initial state:" << endl;
    this->currentState->printMatrix();

    // Expand nodes until optimal path is found
    while (true) {
        // Goal state reached
        if (this->currentState->getMatrix() == this->goalMatrix) {
            costEst = this->currentState->getEstCost();
            // Update min moves
            if (costEst < this->minCost) {
                // First solution found
                if (! this->found) {
                    cout << "First solution found !" << endl << endl;
                    this->found = true;
                // Better solution found
                } else {
                    cout << "More optimal solution found !" << endl << endl;
                }
                this->solvedState = this->currentState;
                this->minCost = costEst;
            // Lesser solution found
            } else {
                cout << "Solution found." << endl << endl;
            }
        // Not goal, expand current node (unless pruned)
        } else if (! this->found || this->currentState->getEstCost() < this->minCost) {
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
        // Loop here if repeated node reached
        while (true) {
            // Pop node off the queue => make it new current node
            this->currentState = this->frontier->top();
            this->frontier->pop();
            stateStr = N_Puzzle::matrixToString(this->currentState->getMatrix());
            // Current node not found in visitedNodes (non-repeated state)
            if (this->visitedNodes.find(stateStr) == visitedNodes.end()) {
                // Mark as visited node
                visitedNodes.insert(stateStr);
                break;
            // No solution found, but frontier empty
            } else if (! this->found && this->frontier->empty()) {
                cout << "This puzzle is unsolvable.  Aborting procedure." << endl;
                return;
            }
        }
        // Display trace if not prunned
        if (this->currentState->getEstCost() < this->minCost) {
            heuristicVal = this->currentState->getHeuristicVal();   // h(n)
            distance = this->currentState->getDistance();           // g(n)
            cout << "The best state to expand with g(n) = " << distance
                 << " & h(n) = " << heuristicVal << " is:" << endl;
            this->currentState->printMatrix();
            cout << "Expanding node..." << endl << endl;
        }
    }
}

void N_Puzzle::makeMoves() {
    shared_ptr<State> nextState;
    for (int move = UP; move <= RIGHT; move++) {
        nextState = this->currentState->makeMove(static_cast<Direction>(move), this->currentState);
        // Only access legal moves
        if (nextState) {
            int heuristicVal = this->heuristic->heuristicValue(nextState);
            nextState->setHeuristicVal(heuristicVal);
            this->frontier->push(nextState);
        }
    }
    // Record largest queue
    if (this->frontier->size() > this->maxNodesInQueue) {
        this->maxNodesInQueue = this->frontier->size();
    }
}

/* Accessor */

void N_Puzzle::printResults() {
    int step = 0;
    stack<shared_ptr<State>> traceBack;
    for (shared_ptr<State> trace = this->solvedState; trace != nullptr; trace = trace->getParent()) {
        traceBack.push(trace);
    }
    cout << "---------------Steps to solve---------------" << endl;
    while (! traceBack.empty()) {
        if (step) cout << "Step " << step << ':' << endl;
        else cout << "Start:" << endl;
        traceBack.top()->printMatrix();
        traceBack.pop();
        step++;
    }
    cout << "-----------------Final step-----------------" << endl;
    cout << "To solve this puzzle, the search algorithm expanded a total of "
         << this->totalNodesExpanded << " node(s)." << endl;
    cout << "The maximum number of nodes in the queue at any one time: " 
         << this->maxNodesInQueue << '.' << endl;
    cout << "This puzzle was solved optimally in " << this->minCost <<" move(s) "
         << "& it took " << this->recordTime << " ms." << endl << endl;
}

/* Static methods */

Matrix N_Puzzle::convertRawMatrix(const vector<int> rawMatrix) {
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

string N_Puzzle::matrixToString(const Matrix matrix) {
    string matrixStr = "[ ";
    for (auto row : matrix) {
        for (auto val : row) {
            matrixStr += (val + ' ');
        }
    }
    return matrixStr + ']';
}
