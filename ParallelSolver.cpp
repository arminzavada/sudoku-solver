//
// Created by Armin on 13/04/2023.
//

#include <thread>
#include <iostream>
#include "ParallelSolver.h"

ParallelSolver::ParallelSolver(std::string const & input, int threads) : SudokuSolver(input), threads(threads) {

}

void ParallelSolver::addNextSteps(std::shared_ptr<SudokuMove> const & move, int x, int y) {
    move->findNextAllowedMove(x, y);

    for (int value = 1; value <= 9; ++value) {
        if (move->isMoveAllowed(x, y, value)) {
            computationQueue.push(Step(move, x, y, value));
        }
    }
}

void ParallelSolver::processNextStep() {
    auto step = computationQueue.getAndPopBlocking();

    if (step.end) {
        return;
    }

    auto move = step.execute();

    if (move->isSolved()) {
        solutions.push_back(move);
        return;
    }

    addNextSteps(move, step.x, step.y);
}

std::list<std::shared_ptr<SudokuMove>> ParallelSolver::solve() {
    addNextSteps(baseMove, 0, 0);

    bool running = true;

    std::list<std::thread> workerThreads;

    for (int i = 0; i < threads; ++i) {
        std::thread workerThread([&] {
            while (running) {
                processNextStep();
            }
        });
        workerThreads.push_back(std::move(workerThread));
    }

    std::thread mainThread([&] {
        computationQueue.threadsWaiting(threads);

        running = false;

        for (int i = 0; i < threads; ++i) {
            computationQueue.push(Step(true));
        }
    });

    mainThread.join();

    for (auto & thread : workerThreads) {
        thread.join();
    }

    return solutions;
}
