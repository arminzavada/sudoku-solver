//
// Created by Armin on 13/04/2023.
//

#include "AutoCountableEvent.h"

void AutoCountableEvent::add() {
    std::lock_guard lk(m);

    count++;
    added.notify_one();
}

void AutoCountableEvent::waitOne() {
    std::unique_lock ul(m);

    waitCount++;
    waiting.notify_one();

    added.wait(ul, [this]() {
        return count > 0;
    });

    waitCount--;
    count--;
}

void AutoCountableEvent::awaitAllWaiting(int waitingThreads) {
    std::unique_lock ul(m);

    waiting.wait(ul, [&]() {
        return waitCount >= waitingThreads;
    });
}
