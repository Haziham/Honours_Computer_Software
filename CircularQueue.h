#pragma once





class CircularQueue
{
public:
    CircularQueue(int size);
    ~CircularQueue();
    int push(char data);
    int pop(char *data);
    bool is_empty();
    bool is_full();
    int count();
    int pushBuffer(char *data, int size);
    int popBuffer(char *data, int size);
    int peekBuffer(char *data, int size);

private:
    char *buffer;
    int head;
    int tail;
    int _size;
    int _count;
};