#include "FixedMultiStack.h"

FixedMultiStack::FixedMultiStack(int stackCapacity)
{
    this->stackCapacity = stackCapacity;                // capacity of each stack
    stackArray = new int[numOfStack * stackCapacity](); // 3 * stackCapacity, elements of whole stack
    stackCapacityUsed = new int[numOfStack]();          // capacity used for each stack
}

FixedMultiStack::~FixedMultiStack() // destructor
{
    delete [] stackArray;   // free dynamically allocated arrays
    delete [] stackCapacityUsed;
}

void FixedMultiStack::push(int stackNum, int value)
{
    if(isFull(stackNum)) {
        std::cout << "Stack" << stackNum << "is full" << std::endl;
    } else {
        stackCapacityUsed[stackNum]++;
        stackArray[indexOfTop(stackNum)] = value;
    }
}

void FixedMultiStack::pop(int stackNum) 
{
    if(isEmpty(stackNum)) {
        std::cout << "Stack" << stackNum << "is empty" << std::endl;
    } else {
        int topIndex = indexOfTop(stackNum);
        stackArray[topIndex] = 0;
        stackCapacityUsed[stackNum]--;
    }
}

int FixedMultiStack::top(int stackNum) const
{
    if(isEmpty(stackNum)) {
        std::cout << "Stack" << stackNum << "is empty" << std::endl;
        exit(1); // or throw exception
    } else {
        return stackArray[indexOfTop(stackNum)];
    }
}

bool FixedMultiStack::isEmpty(int stackNum) const
{
    return (stackCapacityUsed[stackNum] == 0);
}

bool FixedMultiStack::isFull(int stackNum) const
{
    return (stackCapacityUsed[stackNum] == stackCapacity);
}

int FixedMultiStack::indexOfTop(int stackNum) const
{
    int startIndex = stackNum * stackCapacity;
    int capacity = stackCapacityUsed[stackNum];
    return (startIndex + capacity - 1);
}