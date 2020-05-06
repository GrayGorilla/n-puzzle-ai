#ifndef N_PUZZLE_HPP
#define N_PUZZLE_HPP

#include <queue>
#include "../State/State.hpp"
#include "../Heuristic/Heuristic.hpp"

typedef std::priority_queue<std::shared_ptr<State>, std::vector<std::shared_ptr<State>>, StateCompare> CostQueue;

class N_Puzzle {
    private:
        std::shared_ptr<State> currentState;
        std::shared_ptr<State> goalState;
        std::unique_ptr<Heuristic> heuristic;
        std::unique_ptr<CostQueue> frontier;
        bool solved;
        
    public:
        N_Puzzle(const std::vector<int> initial);
        void solve();
        void makeMoves();
        ~N_Puzzle();
};

#endif
