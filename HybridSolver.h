//
// Created by Armin on 13/04/2023.
//

#ifndef SUDOKU_HYBRIDSOLVER_H
#define SUDOKU_HYBRIDSOLVER_H

#include "SudokuSolver.h"

class HybridSolver : public SudokuSolver {
    int magicNumber;
public:
    ~HybridSolver() override = default;

    explicit HybridSolver(std::string const & input, int magicNumber = 300);

    std::list<std::shared_ptr<SudokuMove>> solve() override;
};

#endif //SUDOKU_HYBRIDSOLVER_H
