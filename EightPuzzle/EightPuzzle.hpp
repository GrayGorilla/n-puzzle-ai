#ifndef EIGHT_PUZZLE_HPP
#define EIGHT_PUZZLE_HPP

#include <queue>
#include <vector>
#include <memory>
#include "../State/State.hpp"
#include "../Heuristic/Heuristic.hpp"

typedef std::priority_queue<State, std::vector<State>, StateCompare> CostQueue;

class EightPuzzle {
    private:
        State currentState;
        State goalState;
        std::unique_ptr<Heuristic> heuristic;
        CostQueue frontier;
        
    public:
        EightPuzzle();  // For both constructors, set frontier(StateCompare(true)) before pushing initial state
        EightPuzzle(State currentState);
        int solve();
        ~EightPuzzle();
};

/*
goalState = {
    { 1, 2, 3 },
    { 4, 5, 6 },
    { 7, 8, 0 }
};
*/

#endif
