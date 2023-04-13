#include <iostream>
#include <list>
#include "SudokuMove.h"
#include "Timer.h"
#include "ParallelSolver.h"
#include "HybridSolver.h"
#include "RecursiveSolver.h"
#include <string>
#include <fstream>

void measureTime(std::string const & input, std::unique_ptr<SudokuSolver> solver) {
    std::cout << "Measurement for " << input << " ";

    Timer::measure([&]() {
        solver->solve();
    }, 10);
}

void solveAndPrint(std::unique_ptr<SudokuSolver> solver) {
    std::cout << "Initial configuration: " << std::endl << std::endl;

    solver->print(std::cout);

    std::cout << "Running recursive solver ... " << std::endl << std::endl;

    std::list<std::shared_ptr<SudokuMove>> solutions = solver->solve();

    if (solutions.empty()) {
        std::cout << "There are no solutions for this initial configuration!" << std::endl;
    } else {
        std::cout << solutions.size() << " solution(s) found:" << std::endl;

        for (auto const & solution : solutions) {
            solution->print(std::cout);
        }
    }
}

std::function<std::unique_ptr<SudokuSolver> (std::string const &)> constructSolverFactory(int argc, char *argv[]) {
    if (argc == 3) {
        return [](std::string const &input) { return std::make_unique<RecursiveSolver>(input); };
    }

    std::string name(argv[3]);

    if (name == "recursive") {
        return [](std::string const &input) { return std::make_unique<RecursiveSolver>(input); };
    }

    if (name == "parallel") {
        int threads = 4;

        if (argc == 5) {
            threads = std::stoi(argv[4]);
        }

        return [threads](std::string const &input) { return std::make_unique<ParallelSolver>(input, threads); };
    }

    if (name == "hybrid") {
        int magicNumber = 200;

        if (argc == 5) {
            magicNumber = std::stoi(argv[4]);
        }

        return [magicNumber](std::string const &input) { return std::make_unique<HybridSolver>(input, magicNumber); };
    }

    return [](std::string const &input) { return std::make_unique<RecursiveSolver>(input); };
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        std::cout << "Please specify input file and process mode (measure or solveAndPrint)!" << std::endl;
        return 0;
    }

    std::string file(argv[1]);
    std::string mode(argv[2]);

    if (mode != "measure" && mode != "solveAndPrint") {
        std::cout << "Please specify process mode (measure or solveAndPrint)!" << std::endl;
        return 0;
    }

    auto factory = constructSolverFactory(argc, argv);

    std::ifstream infile(argv[1]);
    std::string line;

    while (std::getline(infile, line))
    {
        if (mode == "measure") {
            measureTime(line, factory(line));
        } else {
            solveAndPrint(factory(line));
        }
    }

    return 0;
}
