//
// Created by Armin on 11/04/2023.
//

#include <memory>
#include <iostream>
#include "SudokuSolver.h"
#include "SudokuMove.h"

SudokuSolver::SudokuSolver(std::string const & input) {
    for (int i = 0; i < 9 * 9; ++i) {
        int x = i % 9;
        int y = i / 9;

        int value = input[i] - '0';

        if (value <= 0 || value > 9) continue;

        baseMove = std::make_shared<SudokuMove>(baseMove, x, y, value);
    }
}

void SudokuSolver::print(std::ostream & os) const {
    baseMove->print(os);
}