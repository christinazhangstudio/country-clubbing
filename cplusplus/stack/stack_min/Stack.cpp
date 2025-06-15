#include "Stack.h"

Stack::Stack() {
    head = nullptr;
    stackSize = 0;
}

Stack::~Stack() {
    StackNode *toRemove;
    while(head != nullptr) {
        toRemove = head;
        head = head->next;
        delete toRemove;
    }
}

void Stack::push(int item) {
    if(isEmpty()) {
        head = new StackNode(item, nullptr);
        head->minimum = head;
    } else if(item <= head->minimum->data) {
        head = new StackNode(item, head);
        head->minimum = head;   // new minimum becomes this node
    } else {
        head = new StackNode(item, head);
        head->minimum = head->next->minimum;    // minimum is the node that is still the minumum
    }

    stackSize++;
}

void Stack::pop() {
    if(stackSize == 0 || head == nullptr) {
        return;
    }
    
    StackNode *toRemove = head;
    head = head->next;
    delete toRemove;
    stackSize--;
}

int Stack::top() const {
    if(stackSize == 0 || head == nullptr) {
        std::cout<< "Stack is empty" << std::endl;
        exit(1);
    }
    return head->data;
}

int Stack::getMinimum() const {
    if(stackSize == 0 || head == nullptr) {
        std::cout<< "Stack is empty" << std::endl;
        exit(1);
    }
    return (head->minimum->data);
}

bool Stack::isEmpty() const{
    return (stackSize == 0 || head == nullptr);
}