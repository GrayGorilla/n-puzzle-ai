#ifndef N_PUZZLE_HPP
#define N_PUZZLE_HPP

#include <queue>
#include <memory>
#include "../State/State.hpp"
#include "../Heuristic/Heuristic.hpp"

typedef std::priority_queue<State, std::vector<State>, StateCompare> CostQueue;

class N_Puzzle {
    private:
        std::shared_ptr<State> currentState;
        std::shared_ptr<State> goalState;
        std::unique_ptr<Heuristic> heuristic;
        std::unique_ptr<CostQueue> frontier;
        
    public:
        N_Puzzle(const std::vector<int> initial);
        int solve();
        ~N_Puzzle();
};

#endif
