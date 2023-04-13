//
// Created by Armin on 11/04/2023.
//

#include <iostream>
#include "SudokuMove.h"

int const allMovesMap = 0b111111111;

int valueToMap(int value) {
    return 1 << (value - 1);
}

SudokuMove::SudokuMove() {
    for (int i = 0; i < 9; ++i) {
        allowedColumns[i] = allMovesMap;
        allowedRows[i] = allMovesMap;
    }

    for (auto & allowedGroup : allowedGroups) {
        for (int & y : allowedGroup) {
            y = allMovesMap;
        }
    }
}

SudokuMove::SudokuMove(SudokuMove const & sudoku) {
    std::copy(&sudoku.allowedRows[0], &sudoku.allowedRows[0] + 9, &allowedRows[0]);
    std::copy(&sudoku.allowedColumns[0], &sudoku.allowedColumns[0] + 9, &allowedColumns[0]);
    std::copy(&sudoku.allowedGroups[0][0], &sudoku.allowedGroups[0][0] + 3*3, &allowedGroups[0][0]);
    std::copy(&sudoku.taken[0], &sudoku.taken[0] + 9, &taken[0]);
}

SudokuMove::SudokuMove(const std::shared_ptr<SudokuMove> &parent, int x, int y, int value) : SudokuMove(*parent) {
    moveX = x;
    moveY = y;
    moveValue = value;
    this->parent = parent;

    int map = valueToMap(value);

    allowedRows[y] &= ~map;
    allowedColumns[x] &= ~map;
    allowedGroups[x / 3][y / 3] &= ~map;
    taken[x] |= (1 << y);
}

void SudokuMove::print(std::ostream & os) const {
    int data[9][9] { };

    data[moveY][moveX] = moveValue;

    auto move = parent;

    while (move != nullptr) {
        data[move->moveY][move->moveX] = move->moveValue;

        move = move->parent;
    }

    for (auto & y : data) {
        for (auto x : y) {
            os << (char)(x + '0') << " ";
        }
        os << std::endl;
    }
    os << std::endl;
}

bool SudokuMove::isSolved() const {
    for (int i : taken) {
        if (i != allMovesMap) {
            return false;
        }
    }
    return true;
}

bool SudokuMove::isMoveAllowed(int x, int y) const {
   return (taken[x] & (1 << y)) == 0;
}

bool SudokuMove::isMoveAllowed(int x, int y, int value) const {
    int map = valueToMap(value);

    return (allowedRows[y] & allowedColumns[x] & allowedGroups[x / 3][y / 3] & map) != 0;
}

void SudokuMove::findNextAllowedMove(int & x, int & y) const {
    for (; x < 9; x++) {
        for (; y < 9; y++) {
            if (isMoveAllowed(x, y)) {
                return;
            }
        }
        y = 0;
    }
}
