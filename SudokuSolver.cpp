//
// Created by Armin on 11/04/2023.
//

#include <memory>
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

void findFirstEmptyCell(const std::shared_ptr<SudokuMove>& move, int & x, int & y) {
    for (x = 0; x < 9; x++) {
        for (y = 0; y < 9; y++) {
            if (move->isMoveAllowed(x, y)) {
                return;
            }
        }
    }
}

void recursiveSolveImpl(const std::shared_ptr<SudokuMove>& move, std::list<std::shared_ptr<SudokuMove>> & solutions) {
    if (move->isSolved()) {
#pragma omp critical
        solutions.push_back(move);
        return;
    }

    int x, y;
    findFirstEmptyCell(move, x, y);

    if (x > 9 || y > 9)
        return; // no more empty cells

    for (int value = 1; value <= 9; ++value) {
        if (move->isMoveAllowed(x, y, value)) {
            auto nextMove = std::make_shared<SudokuMove>(move, x, y, value);
            recursiveSolveImpl(nextMove, solutions);
        }
    }
}

std::list<std::shared_ptr<SudokuMove>> SudokuSolver::recursiveSolve() const {
    std::list<std::shared_ptr<SudokuMove>> solutions;

    recursiveSolveImpl(baseMove, solutions);

    return solutions;
}
