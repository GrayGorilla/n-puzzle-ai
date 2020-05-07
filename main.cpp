#include "N-Puzzle/N-Puzzle.hpp"
using namespace std;

int main() {
    auto puzzle = make_shared<N_Puzzle>(OH_BOY);
    puzzle->createSmartThis(puzzle);
    puzzle->solve();
    return 0;
}
