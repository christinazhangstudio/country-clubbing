#ifndef STACKNODE_H
#define STACKNODE_H

// A forward declaration tells the compiler that a class named Stack exists, 
// but its full definition (i.e., its members and implementation) will be provided later.
// allows you to reference the Stack class (e.g., as a pointer or reference) in the 
// StackNode class without needing the complete definition of Stack at this point.
class Stack;

class StackNode
{
public:
    // The friend keyword declares that the Stack class is a friend of the StackNode class.
    // A friend class has full access to the private and protected members of the class
    // that declares it as a friend. 
    // In this case, Stack can access all private and protected members of StackNode.
    // This is commonly used when Stack needs to manipulate the internal structure of StackNode
    // e.g., accessing or modifying a node’s data or next pointer
    // without exposing those details publicly through getters or setters.
    friend class Stack;
    StackNode(int data, StackNode *next);

private:
    int data;
    StackNode *next;
    StackNode *minimum;
};

#endif