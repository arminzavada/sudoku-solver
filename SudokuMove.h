//
// Created by Armin on 11/04/2023.
//

#ifndef SUDOKU_SUDOKUMOVE_H
#define SUDOKU_SUDOKUMOVE_H


#include <string>
#include <memory>

class SudokuMove {
    std::shared_ptr<SudokuMove> parent = nullptr;

    int taken[9] = {};
    int allowedRows[9] = {};
    int allowedColumns[9] = {};
    int allowedGroups[3][3] = {};
public:
    int moveX = -1;
    int moveY = -1;
    int moveValue = -1;

    SudokuMove();
    SudokuMove(SudokuMove const & sudoku);
    SudokuMove(std::shared_ptr<SudokuMove> const & parent, int x, int y, int value);

    void print(std::ostream & os) const;
    bool isSolved() const;
    bool isMoveAllowed(int x, int y) const;
    bool isMoveAllowed(int x, int y, int value) const;
    void findNextAllowedMove(int & x, int & y) const;
};

#endif //SUDOKU_SUDOKUMOVE_H
