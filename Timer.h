//
// Created by Armin on 11/04/2023.
//

#ifndef SUDOKU_TIMER_H
#define SUDOKU_TIMER_H

#include <chrono>
#include <iostream>
#include <functional>

class Timer
{
private:
    static std::chrono::time_point<std::chrono::high_resolution_clock> t_start;
public:
    static void start() {
        t_start = std::chrono::high_resolution_clock::now();
    }
    static void end(unsigned int nRuns = 1) {
        auto t_end = std::chrono::high_resolution_clock::now();
        std::cout << "CPU [time] "
            << std::chrono::duration_cast<std::chrono::nanoseconds>(t_end - t_start).count() / 1e+06 / nRuns
            << " ms" << " (avg of " << nRuns << ")" << std::endl;
    }
    static void measure(const std::function<void(void)> & program, unsigned int nRuns = 10000) {
        start();
        for (unsigned int i = 0; i < nRuns; ++i)
        {
            program();
        }
        end(nRuns);
    }
};

#endif //SUDOKU_TIMER_H
