#include <iostream>
#include <memory>
#include "EightPuzzle/EightPuzzle.hpp"
using namespace std;

int main() {
    auto puzzle = make_unique<EightPuzzle>();
    puzzle->solve();
    return 0;
}
