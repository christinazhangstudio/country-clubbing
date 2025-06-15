#include <iostream>
#include <cstdlib>

class FixedMultiStack
{
public:
    FixedMultiStack(int stackCapacity);
    // destructor
    // virtual means it can be overridden by derived classes and ensures proper polymorphic behavior 
    // when deleting objects through a base class pointer or reference.
    // The destructor of the most derived class is called first, followed by the destructors of its base classes, ensuring proper cleanup.
    // 
    // If a class is intended to be used as a base class (i.e., other classes may inherit from FixedMultiStack), 
    // and you delete an object of a derived class through a pointer to the base class, 
    // a virtual destructor ensures the derived class’s destructor is called.
    // Without virtual, only the base class’s destructor would be called, 
    // potentially causing resource leaks or undefined behavior in the derived class.
    virtual ~FixedMultiStack();

    // push elem onto stack stackNum, where stackNum is 0 to 2.
    void push(int stackNum, int value);

    void pop(int stackNum);

    int top(int stackNum) const;

    bool isEmpty(int stackNum) const;
    bool isFull(int stackNum) const;

private:
    int numOfStack = 3;
    int stackCapacity;
    int *stackArray;
    int *stackCapacityUsed;

    // return the top index of stack stackNum, where stackNum is 0 to 2.
    int indexOfTop(int stackNum) const;
};

// class FixedMultiStack {
// public:
//     virtual ~FixedMultiStack(); // Virtual destructor
//     // Other members...
// };

// class DerivedStack : public FixedMultiStack {
// public:
//     ~DerivedStack() override {
//         // Clean up derived class resources
//     }
// };

// int main() {
//     FixedMultiStack* ptr = new DerivedStack();
//     delete ptr; // Calls ~DerivedStack(), then ~FixedMultiStack() because destructor is virtual
//     return 0;
// }