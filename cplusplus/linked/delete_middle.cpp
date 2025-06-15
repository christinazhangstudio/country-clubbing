#include <iostream>

using namespace std;

struct Node{
    int data;
    Node* next;
    Node(int d): data{d}, next{nullptr} {};
};

void insert(Node* &head, int data) {
    Node* newNode = new Node(data);
    newNode->next = head;
    head = newNode;
}

int length(Node * head) {
    int count = 0;
    while(head) {
        ++count;
        head = head->next;
    }

    return count;
}

void deleteMiddle(Node * &head) {
    // find the middle
    Node* prevToMiddle = head;
    for(int i = 0; i < length(head)/2 - 1; i++) {
        prevToMiddle = prevToMiddle->next;
    }

    // previous must point to the middle next now
    prevToMiddle->next = prevToMiddle->next->next;
}

void printList(Node * head) {
    Node* curr = head;
    while(curr) {
        cout << "->" << curr->data;
        curr = curr->next;
    }
    cout << endl;
}

int main() {
    Node* head = nullptr;
    for(int i = 0; i < 9; i++) {
        insert(head, rand() % 10);
    }

    cout << "=== original ===" << endl;
    printList(head);
    deleteMiddle(head);

    cout << "=== new ===" << endl;
    printList(head);
}