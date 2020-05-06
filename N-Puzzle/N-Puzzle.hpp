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
        long long recordTime;
        int totalNodesExpanded;
        int maxNodesInQueue;
        int minCost;
        bool found;
        
    public:
        N_Puzzle(const std::vector<int> initial);
        Matrix convertRawMatrix(const std::vector<int> rawMatrix) const;
        void solve();
        void makeMoves();
        void printResults();
        ~N_Puzzle();
};

#endif
