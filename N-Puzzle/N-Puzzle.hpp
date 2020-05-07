#ifndef N_PUZZLE_HPP
#define N_PUZZLE_HPP

#include <queue>
#include <sstream>
#include "../State/State.hpp"
#include "../Heuristic/Heuristic.hpp"

typedef std::priority_queue<std::shared_ptr<State>, std::vector<std::shared_ptr<State>>, StateCompare> CostPriorityQueue;

class N_Puzzle {
    private:
        std::shared_ptr<State> currentState;
        std::shared_ptr<State> solvedState;
        Matrix goalMatrix;
        std::unique_ptr<Heuristic> heuristic;
        std::unique_ptr<CostPriorityQueue> frontier;
        unsigned long long recordTime;
        int totalNodesExpanded;
        int maxNodesInQueue;
        int minCost;
        bool found;
        
    public:
        // Constructor
        N_Puzzle(const std::vector<int> initial);
        // Accessors
        std::shared_ptr<State> getCurrent() const { return this->currentState; }
        void printResults();
        // Mutators
        void solve();
        void makeMoves();
        // Static method
        static Matrix convertRawMatrix(const std::vector<int> rawMatrix);
};

#endif
