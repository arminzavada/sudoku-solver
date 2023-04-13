//
// Created by Armin on 13/04/2023.
//

#ifndef SUDOKU_RECURSIVESOLVER_H
#define SUDOKU_RECURSIVESOLVER_H

#include "SudokuSolver.h"

class RecursiveSolver : public SudokuSolver {
public:
    ~RecursiveSolver() override = default;

    explicit RecursiveSolver(std::string const & input);

    std::list<std::shared_ptr<SudokuMove>> solve() override;
};

void recursiveSolve(std::shared_ptr<SudokuMove> const & move, std::list<std::shared_ptr<SudokuMove>> & solutions, int x, int y);

#endif //SUDOKU_RECURSIVESOLVER_H
