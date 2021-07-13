#pragma once

#include <queue>
#include <mutex>

class SafeQueue
{
private:
    std::mutex mutex;
    std::queue<char*> queue;

public:
    void push(char* packet);
    void pop();
    char* front();
    bool empty();
};