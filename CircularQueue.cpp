#include "CircularQueue.h"
#include <QDebug>

CircularQueue::CircularQueue(int size)
{
    buffer = new char[size];
    head = 0;
    tail = 0;
    _count = 0;
    _size = size;
}


CircularQueue::~CircularQueue()
{
    delete[] buffer;
}

int CircularQueue::push(char data)
{
    if (is_full())
    {
        qDebug() << "Queue is full!";
        return EXIT_FAILURE;
    }
    
    buffer[tail] = data;
    tail = (tail + 1) % _size;
    _count++;
    return EXIT_SUCCESS;
}

int CircularQueue::pop(char* data)
{
    if (is_empty())
    {
        qDebug() << "Queue is empty!";
        return EXIT_FAILURE;
    }
    
    *data = buffer[head];
    head = (head + 1) % _size;
    _count--;
    return EXIT_SUCCESS;
}

bool CircularQueue::is_empty()
{
    return _count == 0;
}

bool CircularQueue::is_full()
{
    return _count == _size;
}

int CircularQueue::count()
{
    return _count;
}

void printBufferAsHex(char *data, int size)
{
    for (int i = 0; i < size; i++)
    {
        qDebug() << QString::number(data[i], 16);
    }
}

int CircularQueue::pushBuffer(char *data, int size)
{
    printBufferAsHex(data, size);
    if (size > _size-_count)
    {
        qDebug() << "Not enough space in queue!";
        return EXIT_FAILURE;
    }


    int spaceRemaining = _size - tail;
    if (size > spaceRemaining)
    {
        memcpy(buffer+tail, data, spaceRemaining);
        memcpy(buffer, data+spaceRemaining, size-spaceRemaining);
    }
    else
    {
        memcpy(buffer+tail, data, size);
    }

    tail = (tail + size) % _size;
    _count += size;
    return EXIT_SUCCESS;
}

int CircularQueue::popBuffer(char *data, int size)
{
    if (size > _count)
    {
        qDebug() << "Not enough data in queue!";
        return EXIT_FAILURE;
    }

    int spaceRemaining = _size - head;
    if (size > spaceRemaining)
    {
        memcpy(data, buffer+head, spaceRemaining);
        memcpy(data+spaceRemaining, buffer, size-spaceRemaining);
    }
    else
    {
        memcpy(data, buffer+head, size);
    }

    head = (head + size) % _size;
    _count -= size;
    return EXIT_SUCCESS;
}

int CircularQueue::peekBuffer(char *data, int size)
{
    if (size > _count)
    {
        qDebug() << "Not enough data in queue!";
        return EXIT_FAILURE;
    }

    int spaceRemaining = _size - head;
    if (size > spaceRemaining)
    {
        memcpy(data, buffer+head, spaceRemaining);
        memcpy(data+spaceRemaining, buffer, size-spaceRemaining);
    }
    else
    {
        memcpy(data, buffer+head, size);
    }

    return 0;
}


