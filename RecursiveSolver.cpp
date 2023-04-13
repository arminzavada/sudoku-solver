//
// Created by Armin on 13/04/2023.
//

#include "RecursiveSolver.h"

RecursiveSolver::RecursiveSolver(const std::string &input) : SudokuSolver(input) {

}

void recursiveSolve(std::shared_ptr<SudokuMove> const & move, std::list<std::shared_ptr<SudokuMove>> & solutions, int x, int y) {
    if (move->isSolved()) {
        solutions.push_back(move);
        return;
    }

    move->findNextAllowedMove(x, y);

    if (x > 9 || y > 9)
        return; // no more empty cells

    for (int value = 1; value <= 9; ++value) {
        if (move->isMoveAllowed(x, y, value)) {
            {
                auto nextMove = std::make_shared<SudokuMove>(move, x, y, value);
                recursiveSolve(nextMove, solutions, x, y);
            }
        }
    }
}

std::list<std::shared_ptr<SudokuMove>> RecursiveSolver::solve() {
    std::list<std::shared_ptr<SudokuMove>> solutions;

    recursiveSolve(baseMove, solutions, 0, 0);

    return solutions;
}
