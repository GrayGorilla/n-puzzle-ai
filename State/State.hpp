#ifndef STATE_HPP
#define STATE_HPP

#include <vector>

typedef std::vector<std::vector<int>> Matrix;

struct State {
    std::vector<std::vector<int>> value;
    int cost;
    State() {}
    State(Matrix value, int cost) : value(value), cost(cost) {}
};

class StateCompare {
    private:
        bool reverse;
    public:
        StateCompare(const bool& revparam = false) : reverse(revparam) {}
        bool operator()(const State& lhs, const State& rhs) const {
            if (reverse) {
                return (lhs.cost > rhs.cost);
            } else {
                return (lhs.cost < rhs.cost);
            }
        }
};

#endif
