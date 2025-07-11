#ifndef THREAD_POOL_H
#define THREAD_POOL_H


#include <mutex>
#include <vector>
#include <queue>
#include <thread>
#include <atomic>
#include <iostream>
#include <functional>
#include <condition_variable>

class ThreadPool {
public:
    ThreadPool(size_t numberOfThreads);
    ~ThreadPool();

    void enqueueTask(std::function<void()> task);
    void waitAll();
private:

    std::atomic<bool> stop;
    std::mutex taskQueueMtx;
    std::condition_variable condition;
    std::queue<std::function<void()>> tasksQueue;
    std::vector<std::thread> workerThreads;

    std::atomic<int> activeTasks;
    std::mutex waitMtx;
    std::condition_variable tasksDoneCondition;

    void workerTask();
};

#endif