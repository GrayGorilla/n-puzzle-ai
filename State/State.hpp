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
        int distance;
        double heuristicVal;
        std::shared_ptr<State> parent;
        // Helpers
        std::pair<int, int> getBlankSpace() const;
        std::shared_ptr<State> copyAndSwap(const std::pair<int, int> a, const std::pair<int, int> b, const std::shared_ptr<State> currState) const;
        void setMatrixDistHeurist(const std::vector<int> rawMatrix, const int distance, const double heuristicVal);
    public:
        // Constructors
        State() : distance(0), heuristicVal(0), parent(nullptr) {}
        State(const std::vector<int> rawMatrix) { this->setMatrixDistHeurist(rawMatrix, 0, 0); this->parent = nullptr; }
        State(const Matrix matrix, const int distance, std::shared_ptr<State> parent) 
            : matrix(matrix), distance(distance), parent(parent), heuristicVal(0) {}
        State(const State& rhs) 
            : matrix(rhs.matrix), distance(rhs.distance), heuristicVal(rhs.heuristicVal), parent(rhs.parent) {}
        State& operator=(const State& rhs) {
            this->matrix = rhs.matrix;
            this->distance = rhs.distance;
            this->heuristicVal = rhs.heuristicVal;
            this->parent = rhs.parent;
        }
        // Accessors
        Matrix getMatrix() const { return this->matrix; }
        int getDistance() const { return this->distance; }
        double getHeuristicVal() const { return this->heuristicVal; }
        double getEstCost() const { return (this->distance + this->heuristicVal); }
        std::shared_ptr<State> getParent() const { return this->parent; }
        void printMatrix() const;
        // Mutators
        void setHeuristicVal(double heuristicVal) { this->heuristicVal = heuristicVal; }
        // Factory
        std::shared_ptr<State> makeMove(const Direction dir, const std::shared_ptr<State> currState) const;
};

class StateCompare {
    private:
        bool reverse;
    public:
        StateCompare(const bool& revparam = false) : reverse(revparam) {}
        bool operator()(const std::shared_ptr<State>& lhs, const std::shared_ptr<State>& rhs) const;
};

#endif
