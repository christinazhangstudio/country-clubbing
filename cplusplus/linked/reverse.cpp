#include <iostream>
#include <random>

using namespace std;

struct Node {
    int data;
    Node* next;
    Node(int d): data{d}, next{nullptr} {}
};

void insert(Node * &head, int d) {
    Node * newNode = new Node(d);
    newNode->next = head;
    head = newNode;
}

void printList(Node *head) {
    while(head != nullptr) {
        cout << head->data << "<-";
        head = head->next;
    }
    cout << endl;
}

void reverse(Node * &head) {
    if(head == nullptr || (head && head->next == nullptr)) {
        return;
    }

    Node *newHead = nullptr;
    Node *nextNode = nullptr;
    while(head) {   
        nextNode = head->next;
        head->next = newHead;
        newHead = head; 
        head = nextNode;
    }
    head = newHead;
}

int main() {
    Node *head = nullptr;
    for(int i = 0; i < 10; i++) {
        insert(head, rand() % 10);
    }

    printList(head);
    reverse(head);
    printList(head);
}