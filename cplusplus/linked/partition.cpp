#include <iostream>
#include <random>

using namespace std;

// nodes less than x come before all the nodes
// greater or equal to x
// (the order is preserved)
// start with the first node
// add everything bigger or equal to x to the tail
// everything smaller gets added after the head

struct Node {
    int data;
    Node* next;
    Node(int d): data{d}, next{nullptr} {};
};

void insert(Node* &head, int data) {
    Node* node = new Node(data);
    node->next = head;
    head = node;
}

void insertBack(Node* &head, int data) {
    Node* node = new Node(data);
    Node* last = head;

    if(head == nullptr) {
        head = node;
    } else {
        while(last->next != nullptr) {
            last = last->next;
        }
        
        last->next = node;
    }
}

void printList(Node *head) {
    while(head != nullptr) {
        cout << "->" << head->data;
        head = head->next;
    }
}

void partition(Node *head, int pivot) {
    // find the pivot
    int i = 0;
    Node *curr = head;
    Node *smaller = nullptr;
    Node *bigger = nullptr;
    Node *pivoted = nullptr;
    while(curr != nullptr) {
        if(curr->data < pivot) {
            insertBack(smaller, curr->data);
        } else if(curr->data > pivot) {
            insertBack(bigger, curr->data);
        } else {
            // pivot stays in the middle
            insertBack(pivoted, curr->data);
        }
        curr = curr->next;
    }

    // printList(smaller);
    // cout << endl;
    // printList(bigger);
    // cout << endl;

    //append the two lists
    Node *smallerLast = smaller;
    while(smallerLast->next != nullptr) {
        smallerLast = smallerLast->next;
    }

    smallerLast->next = pivoted;

    Node *pivotedLast = pivoted;
    while(pivotedLast->next != nullptr) {
        pivotedLast = pivotedLast->next;
    }

    pivotedLast->next = bigger;

    printList(smaller);
}

int main() {
    Node* head = nullptr;
    for(int i = 0; i < 10; i++) {
        insert(head, rand() % 10);
    }

    printList(head);

    cout << endl;
    partition(head, 7);
}