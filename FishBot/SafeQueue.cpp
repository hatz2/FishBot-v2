#include "SafeQueue.h"

void SafeQueue::push(char* packet)
{
    size_t len = strlen(packet);
    char* szPacket = new char[len + 1];

    memcpy(szPacket, packet, len + 1);

    mutex.lock();
    queue.push(szPacket);
    mutex.unlock();
}

void SafeQueue::pop()
{
    mutex.lock();

    char* packet = queue.front();
    queue.pop();
    delete[] packet;

    mutex.unlock();
}

char* SafeQueue::front()
{
    mutex.lock();
    char* packet = queue.front();
    mutex.unlock();

    return packet;
}

bool SafeQueue::empty()
{
    mutex.lock();
    bool isEmpty = queue.empty();
    mutex.unlock();

    return isEmpty;
}