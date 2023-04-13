//
// Created by Armin on 13/04/2023.
//

#ifndef SUDOKU_RECURSIVESOLVER_H
#define SUDOKU_RECURSIVESOLVER_H

#include "SudokuSolver.h"

class RecursiveSolver : public SudokuSolver {
public:
    explicit RecursiveSolver(std::string const & input);

    virtual std::list<std::shared_ptr<SudokuMove>> solve();
};


#endif //SUDOKU_RECURSIVESOLVER_H
