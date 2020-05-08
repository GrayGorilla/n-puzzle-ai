#include <chrono>
#include <stack>
#include <cmath>
#include <sstream>
#include "N-Puzzle.hpp"
using namespace std;

/* Constructor */

N_Puzzle::N_Puzzle() {
    int puzzLength = sqrt(PUZZLE + 1);

    // Exit if puzzle type invalid
    if (puzzLength != floor(puzzLength)) {
        cerr << "Puzzle type is not valid.  Exiting program." << endl;
        exit(1);
    }
    // Set current & goal states
    this->frontier = make_unique<CostPriorityQueue>(StateCompare(true));
    this->goalMatrix = N_Puzzle::convertRawMatrix(GOAL);
    this->found = false;
    this->totalNodesExpanded = 0;
    this->maxNodesInQueue = 0;
    this->minCost = static_cast<int>INFINITY;
    this->greetUser();
}

/* Mutators */

void N_Puzzle::greetUser() {
    string puzzleStr, rowOneStr, rowTwoStr, rowThreeStr, elementStr, algorithmStr;
    vector<int> usersMatrix;
    int puzzle, element, algorithm;
    bool valid = true;
    stringstream ss;

    cout << "\n------------ Welcome to 862090718 Eight-Puzzle solver ------------" << endl;
    // Select puzzle
    do {
        cout << "Type '1' to use a default puzzle, or '2' to enter your own puzzle." << endl << ">  ";
        getline(cin, puzzleStr);
        puzzle = stoi(puzzleStr);
        switch (puzzle) {
            // Default puzzle (OH_BOY arg: replace with any default puzzle stored in global.hpp)
            case 1:
                this->frontier->emplace(make_shared<State>(OH_BOY));
                valid = true;
                break;
            // Custom puzzle
            case 2:
                cout << "\nEnter your puzzle, use a zero to represent the blank." << endl
                     << "Enter the 1st row, use spaces or tabs between numbers:  ";
                getline(cin, rowOneStr);
                cout << "Enter the 2nd row, use spaces or tabs between numbers:  ";
                getline(cin, rowTwoStr);
                cout << "Enter the 3rd row, use spaces or tabs between numbers:  ";
                getline(cin, rowThreeStr);

                ss << rowOneStr << ' ' << rowTwoStr << ' ' << rowThreeStr;
                cout << "Elements:";
                while (ss >> elementStr) {
                    cout << " " << elementStr;
                    element = stoi(elementStr);
                    usersMatrix.push_back(element);
                }
                cout << '\n';
                this->frontier->emplace(make_shared<State>(usersMatrix));
                valid = true;
                break;
            default:
                cout << "Invalid entry." << endl << endl;
                valid = false;
                break;
        }
    } while (! valid);
    cout << endl;
    
    // Select algorithm
    do {
        cout << "Enter your choice of algorithm." << endl
             << "1:  Uniform Cost Search" << endl
             << "2:  A* with the Misplaced Tile heuristic." << endl
             << "3:  A* with the Eucledian Distance heuristic." << endl << ">  ";
        getline(cin, algorithmStr);
        algorithm = stoi(algorithmStr);
        switch (algorithm) {
            // Uniform Cost Search
            case 1:
                this->heuristic = make_unique<UniformCostSearch>();
                valid = true;
                break;
            case 2:
                this->heuristic = make_unique<AStarMisplacedTile>();
                valid = true;
                break;
            case 3:
                this->heuristic = make_unique<AStarEuclidianDistance>();
                valid = true;
                break;
            default:
                cout << "Invalid entry." << endl << endl;
        }
    } while (! valid);
    cout << endl;
}

void N_Puzzle::solve() {
    int distance, heuristicVal, costEst;
    // string stateStr;
    auto startTime = chrono::high_resolution_clock::now();

    cout << "Solving..." << endl << endl;
    // Pop initial state from frontier
    this->currentState = this->frontier->top();
    this->frontier->pop();
    // Allow repeats of goalMatricies, but no other repeats
    if (this->currentState->getMatrix() != this->goalMatrix) {
        // Mark as visited node
        this->visitedNodes.insert(N_Puzzle::matrixToString(this->currentState->getMatrix()));
    }
    // Print initial state
    cout << "Expanding initial state:" << endl;
    this->currentState->printMatrix();

    // Expand nodes until optimal path is found
    while (true) {
        // Goal state reached
        if (this->currentState->getMatrix() == this->goalMatrix) {
            costEst = this->currentState->getEstCost();
            // Optimal solution found; update min moves
            if (costEst < this->minCost) {
                this->found = true;
                this->solvedState = this->currentState;
                this->minCost = costEst;
            }
        // Not goal, expand current node (unless pruned)
        } else if (! this->found || this->currentState->getEstCost() < this->minCost) {
            this->makeMoves();
            this->totalNodesExpanded++;
        }
        // End Puzzle
        if (this->frontier->empty()) {
            // Impossible Puzzle discovered
            if (! this->found) {
                auto endTime = chrono::high_resolution_clock::now();
                auto time = endTime - startTime;
                this->recordTime = time / chrono::milliseconds(1);
                cout << "Discovery - This puzzle is unsolvable." << endl << endl
                     << "Nodes expanded: " << this->totalNodesExpanded << "nodes"<< endl
                     << "Largest queue: " << this->maxNodesInQueue << "nodes" << endl
                     << "Time elapsed: " << this->recordTime << "ms" << endl
                     << "Aborting procedure." << endl;
                return;
            // Optimal solution locked in
            } else {
                auto endTime = chrono::high_resolution_clock::now();
                auto time = endTime - startTime;
                this->recordTime = time / chrono::milliseconds(1);
                cout << "Solved !!!" << endl << endl;
                this->printResults();
                break;
            }
        }
        // Pop node off the queue => make it new current node
        this->currentState = this->frontier->top();
        this->frontier->pop();
        // Display trace for new currentState if not prunned
        if (! this->found || this->currentState->getEstCost() < this->minCost) {
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
    string nodeStr;
    for (int move = UP; move <= RIGHT; move++) {
        nextState = this->currentState->makeMove(static_cast<Direction>(move), this->currentState);
        // Only access legal moves
        if (nextState) {
            auto nextNode = nextState->getMatrix();
            nodeStr = N_Puzzle::matrixToString(nextState->getMatrix());
            // Only add non-repeating states to frontier
            if (this->visitedNodes.find(nodeStr) == visitedNodes.end()) {
                // Allow repeats of goalMatricies but no other repeats
                if (nextNode != this->goalMatrix) {
                    this->visitedNodes.insert(nodeStr);
                }
                int heuristicVal = this->heuristic->heuristicValue(nextState);
                nextState->setHeuristicVal(heuristicVal);
                this->frontier->push(nextState);
            }
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
    cout << "-------------Final step reached-------------" << endl;
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
