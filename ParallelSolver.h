//
// Created by Armin on 13/04/2023.
//

#ifndef SUDOKU_PARALLELSOLVER_H
#define SUDOKU_PARALLELSOLVER_H


#include <list>
#include "BlockingQueue.h"
#include "SudokuMove.h"
#include "SudokuSolver.h"
#include "Step.h"

class ParallelSolver : public SudokuSolver {
    int const threads;

    BlockingQueue<Step> computationQueue;
    std::list<std::shared_ptr<SudokuMove>> solutions;

    void addNextSteps(std::shared_ptr<SudokuMove> const & move, int x, int y);
    void processNextStep();
public:
    ~ParallelSolver() override = default;

    explicit ParallelSolver(std::string const & input, int threads = 1);

    std::list<std::shared_ptr<SudokuMove>> solve() override;
};

#endif //SUDOKU_PARALLELSOLVER_H
