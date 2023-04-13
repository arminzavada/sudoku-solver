//
// Created by Armin on 13/04/2023.
//

#ifndef SUDOKU_BLOCKINGQUEUE_H
#define SUDOKU_BLOCKINGQUEUE_H

#include <queue>
#include "AutoCountableEvent.h"

template<class T>
class BlockingQueue {
    AutoCountableEvent incomingData;

    std::queue<T> queue;
    std::mutex m;
public:
    T getAndPopBlocking();
    void push(T const & t);
    void push(T && t);
    void threadsWaiting(int waitingThreads);
};

template<class T>
void BlockingQueue<T>::threadsWaiting(int waitingThreads) {
    incomingData.awaitAllWaiting(waitingThreads);
}

template<class T>
T BlockingQueue<T>::getAndPopBlocking() {
    incomingData.waitOne();

    std::lock_guard lk(m);

    auto temp = queue.front();

    queue.pop();

    return temp;
}

template<class T>
void BlockingQueue<T>::push(T const & t) {
    std::lock_guard lk(m);

    queue.push(t);

    incomingData.add();
}

template<class T>
void BlockingQueue<T>::push(T && t) {
    std::lock_guard lk(m);

    queue.push(std::move(t));

    incomingData.add();
}

#endif //SUDOKU_BLOCKINGQUEUE_H
