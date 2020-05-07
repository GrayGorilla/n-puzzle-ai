#include "N-Puzzle/N-Puzzle.hpp"
using namespace std;

int main() {
    auto puzzle = make_shared<N_Puzzle>();
    puzzle->solve();
    return 0;
}
