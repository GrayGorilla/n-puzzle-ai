#ifndef HEURISTIC_HPP
#define HEURISTIC_HPP

#include <memory>

class N_Puzzle;

class Heuristic {
    public:
        Heuristic() {}
        virtual int heuristicValue(std::shared_ptr<N_Puzzle> puzzle) = 0;
};

class UniformCostSearch : Heuristic {
    public:
        UniformCostSearch() {}
        virtual int heuristicValue(std::shared_ptr<N_Puzzle> puzzle) override;
};

class aStarMisplacedTile : Heuristic {
    public:
        aStarMisplacedTile() {}
        virtual int heuristicValue(std::shared_ptr<N_Puzzle> puzzle) override;
};

class aStarEuclidianDistance : Heuristic {
    public:
        aStarEuclidianDistance() {}
        virtual int heuristicValue(std::shared_ptr<N_Puzzle> puzzle) override;
};

#endif
