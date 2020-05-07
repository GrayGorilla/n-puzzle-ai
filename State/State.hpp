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
        // Helpers
        std::pair<int, int> getBlankSpace() const;
        std::shared_ptr<State> copyAndSwap(const std::pair<int, int> a, const std::pair<int, int> b) const;
        void setMatrixDistHeurist(const std::vector<int> rawMatrix, const int distance, const double heuristicVal);
    public:
        // Constructors
        State() : distance(0), heuristicVal(0) {}
        State(const Matrix matrix, const int distance) : matrix(matrix), distance(distance), heuristicVal(0) {}
        State(const std::vector<int> rawMatrix) { this->setMatrixDistHeurist(rawMatrix, 0, 0); }
        State(const State& rhs) : matrix(rhs.matrix), distance(rhs.distance) {}
        State& operator=(const State& rhs) {
            this->matrix = rhs.matrix;
            this->distance = rhs.distance;
        }
        // Accessors
        Matrix getMatrix() const { return this->matrix; }
        int getDistance() const { return this->distance; }
        double getHeuristicVal() const { return this->heuristicVal; }
        double getEstCost() const { return (this->distance + this->heuristicVal); }
        void printMatrix() const;
        // Mutators
        void setHeuristicVal(double heuristicVal) { this->heuristicVal = heuristicVal; }
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
