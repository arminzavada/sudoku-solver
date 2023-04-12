#include <iostream>
#include <list>
#include "SudokuMove.h"
#include "SudokuSolver.h"
#include "Timer.h"

void measureTime(std::string const & input) {
    SudokuSolver map(input);

    std::cout << "Measurement for " << input << " ";
    Timer::measure([&]() {
        map.recursiveSolve();
    }, 10);
}

void solveAndPrint(std::string const & input) {
    SudokuSolver map(input);

    std::cout << "Initial configuration: " << std::endl;

    map.print(std::cout);

    std::cout << "Running recursive solver ... " << std::endl << std::endl;

    std::list<std::shared_ptr<SudokuMove>> solutions = map.recursiveSolve();

    if (solutions.empty()) {
        std::cout << "There are no solutions for this initial configuration!" << std::endl;
    } else {
        std::cout << solutions.size() << " solution(s) found:" << std::endl;

        for (auto const & solution : solutions) {
            solution->print(std::cout);
        }
    }
}

#include <string>
#include <fstream>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        std::cout << "Please specify input file and process mode (measure or solveAndPrint)!" << std::endl;
        return 0;
    }

    std::string file(argv[1]);
    std::string mode(argv[2]);

    if (mode != "measure" && mode != "solveAndPrint") {
        std::cout << "Please specify process mode (measure or solveAndPrint)!" << std::endl;
        return 0;
    }

    std::ifstream infile(argv[1]);
    std::string line;

    while (std::getline(infile, line))
    {
        if (mode == "measure") {
            measureTime(line);
        } else {
            solveAndPrint(line);
        }
    }

    return 0;
}
