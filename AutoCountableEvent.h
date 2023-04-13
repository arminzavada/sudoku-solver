//
// Created by Armin on 13/04/2023.
//

#ifndef SUDOKU_AUTOCOUNTABLEEVENT_H
#define SUDOKU_AUTOCOUNTABLEEVENT_H

#include <pthread.h>
#include <mutex>
#include <condition_variable>

class AutoCountableEvent {
    int count = 0;
    int waitCount = 0;

    std::mutex m;
    std::condition_variable added;
    std::condition_variable waiting;
public:
    AutoCountableEvent() = default;
    AutoCountableEvent(AutoCountableEvent const &) = delete;
    AutoCountableEvent& operator=(AutoCountableEvent const &) = delete;

    void add();
    void waitOne();
    void awaitAllWaiting(int waitingThreads);
};


#endif //SUDOKU_AUTOCOUNTABLEEVENT_H
