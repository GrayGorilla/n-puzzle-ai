#ifndef N_PUZZLE_HPP
#define N_PUZZLE_HPP

#include <queue>
#include <vector>
#include <memory>
#include "../State/State.hpp"
#include "../Heuristic/Heuristic.hpp"

typedef std::priority_queue<State, std::vector<State>, StateCompare> CostQueue;

class N_Puzzle {
    private:
        State currentState;
        State goalState;
        std::unique_ptr<Heuristic> heuristic;
        CostQueue frontier;
        
    public:
        N_Puzzle();  // For both constructors, set frontier(StateCompare(true)) before pushing initial state
        N_Puzzle(State currentState);
        int solve();
        std::vector<int> randomPuzzle();
        ~N_Puzzle();
};

#endif
