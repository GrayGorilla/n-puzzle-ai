#include <cmath>
#include "State.hpp"
using namespace std;

void State::setMatrix(const vector<int> rawMatrix, int cost) {
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

void State::printMatrix() const {
    for (auto col : this->matrix) {
        for (auto val : col) {
            cout << val << ' ';
        }
        cout << endl;
    }
    cout << endl;
}

// Enables reversing priority queue
bool StateCompare::operator()(const State& lhs, const State& rhs) const {
    if (this->reverse) {
        return (lhs.getCost() > rhs.getCost());
    } else {
        return (lhs.getCost() < rhs.getCost());
    }
}
