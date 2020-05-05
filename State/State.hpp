#ifndef STATE_HPP
#define STATE_HPP

#include <iostream>
#include <vector>
#include "../globals.hpp"

typedef std::vector<std::vector<int>> Matrix;

class State {
    private:
        Matrix matrix;
        int cost;
    public:
        State() : cost(0) {}
        State(std::vector<int> rawMatrix) { this->setMatrix(rawMatrix, 0); }
        State(const State& rhs) : matrix(rhs.matrix), cost(rhs.cost) {}
        State& operator=(const State& rhs) {
            this->matrix = rhs.matrix;
            this->cost = rhs.cost;
        }
        Matrix getMatrix() const { return this->matrix; }
        int getCost() const { return this->cost; }
        void setMatrix(std::vector<int> rawMatrix);
        void setMatrix(std::vector<int> rawMatrix, int cost);
        void printMatrix() const;
        State makeMove();
        ~State() { std::cout << "State de-allocated.\n"; }
};

class StateCompare {
    private:
        bool reverse;
    public:
        StateCompare(const bool& revparam = false) : reverse(revparam) {}
        bool operator()(const State& lhs, const State& rhs) const;
};

#endif
