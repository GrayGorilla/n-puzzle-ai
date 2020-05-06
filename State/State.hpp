#ifndef STATE_HPP
#define STATE_HPP

#include <memory>
#include <utility>
#include <iostream>
#include "../globals.hpp"

typedef std::vector<std::vector<int>> Matrix;

class State {
    private:
        Matrix matrix;
        int cost;
        // Helpers
        std::pair<int, int> getBlankSpace() const;
        std::shared_ptr<State> copyAndSwap(const std::pair<int, int> a, const std::pair<int, int> b) const;
    public:
        // Constructors
        State() : cost(0) {}
        State(const Matrix matrix, const int cost) : matrix(matrix), cost(cost) {}
        State(const std::vector<int> rawMatrix, const int cost) { this->setMatrixAndCost(rawMatrix, cost); }
        State(const State& rhs) : matrix(rhs.matrix), cost(rhs.cost) {}
        State& operator=(const State& rhs) {
            this->matrix = rhs.matrix;
            this->cost = rhs.cost;
        }
        // Accessors
        Matrix getMatrix() const { return this->matrix; }
        int getCost() const { return this->cost; }
        void printMatrix() const;
        // Mutators
        void setMatrixAndCost(const std::vector<int> rawMatrix, const int cost);
        void setCost(int cost) { this->cost = cost; }
        // Factory
        std::shared_ptr<State> makeMove(const Direction dir) const;
        // Destructor
        ~State() { std::cout << "<State de-allocated>" << std::endl; }
};

class StateCompare {
    private:
        bool reverse;
    public:
        StateCompare(const bool& revparam = false) : reverse(revparam) {}
        bool operator()(const std::shared_ptr<State>& lhs, const std::shared_ptr<State>& rhs) const;
};

#endif
