#ifndef HEURISTIC_HPP
#define HEURISTIC_HPP

#include <memory>

class State;

class Heuristic {
    public:
        Heuristic() {}
        virtual int heuristicValue(const std::shared_ptr<State> nextState) = 0;
};

class UniformCostSearch : public Heuristic {
    public:
        UniformCostSearch() {}
        virtual int heuristicValue(const std::shared_ptr<State> nextState) override;
};

class AStarMisplacedTile : public Heuristic {
    public:
        AStarMisplacedTile() {}
        virtual int heuristicValue(const std::shared_ptr<State> nextState) override;
};

class AStarEuclidianDistance : public Heuristic {
    public:
        AStarEuclidianDistance() {}
        virtual int heuristicValue(const std::shared_ptr<State> nextState) override;
};

#endif
