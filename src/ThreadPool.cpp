#include "../include/ThreadPool.h"

ThreadPool::ThreadPool(size_t numberOfThreads) : stop(false), activeTasks(0) {
    for(size_t i = 0;i < numberOfThreads;i++) {
        workerThreads.emplace_back([this]() {
            this->workerTask();
        });
    }
}

void ThreadPool::enqueueTask(std::function<void()> task) {
    {
        std::unique_lock<std::mutex> lock(taskQueueMtx);
        tasksQueue.push(task);
    }
    condition.notify_one();
}

void ThreadPool::workerTask() {
    while(true) {
        std::function<void()> task;
        {
            std::unique_lock<std::mutex> lock(taskQueueMtx);
            condition.wait(lock, [this]() {
                return stop || !tasksQueue.empty();
            });

            if(stop && tasksQueue.empty()) return;
            task = std::move(tasksQueue.front());
            tasksQueue.pop();

            activeTasks++;
            task();

            {
                std::lock_guard<std::mutex> lock(waitMtx);
                activeTasks--;
                if(tasksQueue.empty() && activeTasks == 0) {
                    tasksDoneCondition.notify_all();
                }
            }
        }
    }
}

void ThreadPool::waitAll() {
    std::unique_lock<std::mutex> lock(waitMtx);
    tasksDoneCondition.wait(lock, [this]() {
        return tasksQueue.empty() && activeTasks == 0;
    });
}

ThreadPool::~ThreadPool() {
    {
        std::lock_guard<std::mutex> lock(taskQueueMtx);
        stop = true;
    }

    condition.notify_all();
    for(auto &worker: workerThreads) {
        if(worker.joinable())
            worker.join();
    }
    std::cout << "All threads have been destroyed\n";
}