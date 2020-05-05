#include <iostream>
#include <memory>
#include "N-Puzzle/N-Puzzle.hpp"
using namespace std;

int main() {
    auto puzzle = make_unique<N_Puzzle>();
    puzzle->solve();
    return 0;
}
