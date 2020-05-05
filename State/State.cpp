#include <cmath>
#include "State.hpp"
using namespace std;

void State::setMatrix(vector<int> rawMatrix) {
    int count = 1, puzzLength = sqrt(rawMatrix.size());
    vector<int> row;
    this->matrix.clear();

    for (auto val : rawMatrix) {
        if (count % puzzLength == 0) {
            this->matrix.push_back(row);
            row.clear();
        }
        row.push_back(val);
        count++;
    }
}

void State::setMatrix(vector<int> rawMatrix, int cost) {
    this->setMatrix(rawMatrix);
    this->cost = cost;
}

void State::printMatrix() const {
    for (auto col : this->matrix) {
        for (auto val : col) {
            cout << val << ' ';
        }
        cout << endl;
    }
}

// Enables reversing priority queue
bool StateCompare::operator()(const State& lhs, const State& rhs) const {
    if (this->reverse) {
        return (lhs.getCost() > rhs.getCost());
    } else {
        return (lhs.getCost() < rhs.getCost());
    }
}
