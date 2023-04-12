//
// Created by Armin on 11/04/2023.
//

#ifndef SUDOKU_SUDOKUSOLVER_H
#define SUDOKU_SUDOKUSOLVER_H

#include <string>
#include <list>
#include "SudokuMove.h"

class SudokuSolver {
    std::shared_ptr<SudokuMove> baseMove = std::make_shared<SudokuMove>();
public:
    explicit SudokuSolver(std::string const & input);

    void print(std::ostream & os) const;
    std::list<std::shared_ptr<SudokuMove>> recursiveSolve() const;
};


#endif //SUDOKU_SUDOKUSOLVER_H
