//
// Created by Armin on 11/04/2023.
//

#ifndef SUDOKU_SUDOKUSOLVER_H
#define SUDOKU_SUDOKUSOLVER_H

#include <string>
#include <list>
#include "SudokuMove.h"

class SudokuSolver {
protected:
    std::shared_ptr<SudokuMove> baseMove = std::make_shared<SudokuMove>();
public:
    explicit SudokuSolver(std::string const & input);
    virtual ~SudokuSolver() = default;

    void print(std::ostream & os) const;

    virtual std::list<std::shared_ptr<SudokuMove>> solve() = 0;
};


#endif //SUDOKU_SUDOKUSOLVER_H
