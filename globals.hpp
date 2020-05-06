#ifndef GLOBALS_HPP
#define GLOBALS_HPP

#include <vector>

enum Direction { UP, DOWN, LEFT, RIGHT };
const int PUZZLE = 8;
const int PUZZLE_LENGTH = 3;

// Raw Matricies
const std::vector<int> GOAL = { 1, 2, 3, 4, 5, 6, 7, 8, 0 };
const std::vector<int> TRIVIAL = { 1, 2, 3, 4, 5, 6, 7, 8, 0 };
const std::vector<int> VERY_EASY = { 1, 2, 3, 4, 5, 6, 7, 0, 8 };
const std::vector<int> EASY = { 1, 2, 0, 4, 5, 3, 7, 8, 6 };
const std::vector<int> DOABLE = { 0, 1, 2, 4, 5, 3, 7, 8, 6 };
const std::vector<int> OH_BOY = { 8, 7, 1, 6, 0, 2, 5, 4, 3 };
const std::vector<int> IMPOSSIBLE = { 1, 2, 3, 4, 5, 6, 8, 7, 0 };
const std::vector<int> SUBMISSION_PROBLEM = { 1, 0, 3, 4, 2, 6, 7, 5, 8 };

#endif
