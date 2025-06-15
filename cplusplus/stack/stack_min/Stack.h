#ifndef STACK_H
#define STACK_H

// ^^ include guard (also called a header guard). 
// prevent the header file from being included multiple times in a single compilation unit, 
// which avoids duplicate definition errors.

// a problem if you have something like:
// // // main.cpp
// #include "FixedMultiStack.h"
// #include "OtherFile.h"

// // // OtherFile.h
// #include "FixedMultiStack.h"

#include "StackNode.h"
#include <iostream>
#include <cstdlib>

class Stack
{
public:
    Stack();
    virtual ~Stack();
    void push(int item);
    void pop();
    int top() const;
    int getMinimum() const;

    bool isEmpty() const;
    int getSize() const;
private:
    StackNode *head;
    int stackSize;
};

#endif