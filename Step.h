//
// Created by Armin on 13/04/2023.
//

#ifndef SUDOKU_STEP_H
#define SUDOKU_STEP_H


#include <memory>
#include "SudokuMove.h"

class Step {
public:
    std::shared_ptr<SudokuMove> move = nullptr;
    int x = -1;
    int y = -1;
    int value = 0;
    bool end = false;

    std::shared_ptr<SudokuMove> execute() const;

    Step(std::shared_ptr<SudokuMove> move, int x, int y, int value);
    explicit Step(bool end);

};


#endif //SUDOKU_STEP_H
