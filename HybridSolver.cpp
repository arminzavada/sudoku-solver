//
// Created by Armin on 13/04/2023.
//

#include <vector>
#include "HybridSolver.h"
#include "RecursiveSolver.h"

HybridSolver::HybridSolver(std::string const & input, int magicNumber) : SudokuSolver(input), magicNumber(magicNumber) {

}

bool preprocessLayer(std::vector<std::shared_ptr<SudokuMove>> & collection, std::shared_ptr<SudokuMove> const & move, int x, int y) {
    move->findNextAllowedMove(x, y);

    if (x >= 9 || y >= 9) {
        collection.push_back(move);

        return false;
    }

    for (int value = 1; value <= 9; ++value) {
        if (move->isMoveAllowed(x, y, value)) {
            collection.push_back(std::make_shared<SudokuMove>(move, x, y, value));
        }
    }

    return true;
}

std::vector<std::shared_ptr<SudokuMove>> preprocess(std::shared_ptr<SudokuMove> const & baseMove, int magicNumber, int x, int y) {
    std::vector<std::shared_ptr<SudokuMove>> preprocessedMoves;

    preprocessedMoves.push_back(baseMove);

    bool canGenerateMore = true;

    while (preprocessedMoves.size() < magicNumber && canGenerateMore) {
        std::vector<std::shared_ptr<SudokuMove>> temp;

        for (auto & move : preprocessedMoves) {
            canGenerateMore &= preprocessLayer(temp, move, x, y);
        }

        preprocessedMoves = std::move(temp);
    }

    return preprocessedMoves;
}

std::list<std::shared_ptr<SudokuMove>> HybridSolver::solve() {
    std::list<std::shared_ptr<SudokuMove>> solutions;

    std::vector<std::shared_ptr<SudokuMove>> preprocessedMoves = preprocess(baseMove, magicNumber, 0, 0);

#pragma omp parallel for default(none) shared(preprocessedMoves, solutions)
    for (auto & move : preprocessedMoves) {
        recursiveSolve(move, solutions, 0, 0);
    }

    return solutions;
}
