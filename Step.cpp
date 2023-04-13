//
// Created by Armin on 13/04/2023.
//

#include "Step.h"

#include <utility>

Step::Step(std::shared_ptr<SudokuMove> move, int x, int y, int value) : move(std::move(move)), x(x), y(y), value(value), end(false) {

}

Step::Step(bool end) : move(nullptr), x(-1), y(-1), value(-1), end(end) {

}

std::shared_ptr<SudokuMove> Step::execute() const {
    return std::make_shared<SudokuMove>(move, x, y, value);
}
