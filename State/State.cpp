#include <cmath>
#include "State.hpp"
using namespace std;

/* State method implementations */

// Helpers
pair<int, int> State::getBlankSpace() const {
    int x = 0, y = 0;
    // If no matrix, return error pair
    if (this->matrix.empty()) {
        cerr << "No matrix found." << endl;
        return make_pair(-1, -1);
    }
    for (auto row : this->matrix) {
        for (auto val : row) {
            if (val == 0) {
                return make_pair(y, x);
            } else {
                x++;
            }
        }
        x = 0;
        y++;
    }
    // If no 0 value, return error pair
    cerr << "No blank space found." << endl;
    return make_pair(-2, -2);
}

shared_ptr<State> State::copyAndSwap(const pair<int, int> a, const pair<int, int> b) const {
    Matrix child = this->matrix;
    int x = child.at(a.first).at(a.second);
    int y = child.at(b.first).at(b.second);

    child[a.first][a.second] = y;
    child[b.first][b.second] = x;
    return make_shared<State>(child, this->cost);
}

// Accessors
void State::printMatrix() const {
    for (auto row : this->matrix) {
        for (auto val : row) {
            // Print value or * if value == 0
            if (val) cout << val << ' ';
            else cout << "* ";
        }
        cout << endl;
    }
    cout << endl;
}

// Mutators
void State::setMatrixAndCost(const vector<int> rawMatrix, const int cost) {
    int count = 1, puzzLength = sqrt(rawMatrix.size());
    vector<int> row;
    this->matrix.clear();

    for (auto val : rawMatrix) {
        row.push_back(val);
        count++;
        if (count % puzzLength != 1) continue;
        
        this->matrix.push_back(row);
        row.clear();
    }
    this->cost = cost;
}

// Factory
shared_ptr<State> State::makeMove(Direction dir) const {
    pair<int, int> blankSpace = this->getBlankSpace();
    pair<int, int> destination;
    switch (dir) {
        case UP:
            if (blankSpace.first > 0) {
                destination = make_pair(blankSpace.first - 1, blankSpace.second);
                return copyAndSwap(blankSpace, destination);
            } else {
                return nullptr;
            }
        case DOWN:
            if (blankSpace.first < PUZZLE_LENGTH - 1) {
                destination = make_pair(blankSpace.first + 1, blankSpace.second);
                return copyAndSwap(blankSpace, destination);
            } else {
                return nullptr;
            }
        case LEFT:
            if (blankSpace.second > 0) {
                destination = make_pair(blankSpace.first, blankSpace.second - 1);
                return copyAndSwap(blankSpace, destination);
            } else {
                return nullptr;
            }
        case RIGHT:
            if (blankSpace.second < PUZZLE_LENGTH - 1) {
                destination = make_pair(blankSpace.first, blankSpace.second + 1);
                return copyAndSwap(blankSpace, destination);
            } else {
                return nullptr;
            }
        default:
            return nullptr;
    }
}

/* StateCompare method implementations */

// Enables reversing priority queue
bool StateCompare::operator()(const std::shared_ptr<State>& lhs, const std::shared_ptr<State>& rhs) const {
    if (this->reverse) {
        return (lhs->getCost() > rhs->getCost());
    } else {
        return (lhs->getCost() < rhs->getCost());
    }
}
