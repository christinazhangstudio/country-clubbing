#include <iostream>

using namespace std;

struct Node {
    int data;
    Node* next;
    Node(int d) : data{d}, next{nullptr} {}
};

void insert(Node * &head, int data) {
    Node* newNode = new Node(data);
    newNode->next = head;
    head = newNode;
}

// DO NOT PASS IN Node* &head, YOU WILL EMPTY OUT THE LIST SINCE BY REF
void printList(Node* head) {
    while(head) {
        cout << " <- " << head->data;
        head = head->next;
    }
    cout << endl;
}

Node* kthToLastIterative(Node *head, int k) {
    if(head == nullptr) {
        return head;
    }
 
    // kthFromLast = size of linked list - kthFromHead

    Node* kthFromHead = head;
    Node *kthFromLast = head;

    int i = 0;
    while(i < k && kthFromHead) {
        kthFromHead = kthFromHead->next;
        ++i;
    }

    while(kthFromHead != nullptr) {
        kthFromHead = kthFromHead->next;
        kthFromLast = kthFromLast->next;
    }

    return kthFromLast;
}

int main() {
    Node* head = nullptr;
    for(int i = 0; i < 10; i++) {
        insert(head, rand() % 10);
    }

    cout << "=== original ===" << endl;
    printList(head);
    Node* node = kthToLastIterative(head, 4);
    cout << "node: " << node->data << endl;;

    Node* head2 = nullptr;
    for(int i = 0; i < 10; i++) {
        insert(head2, rand() % 10);
    }

    cout << "=== original ===" << endl;
    printList(head2);
    Node* node2 = kthToLastIterative(head2, 1);
    cout << "node: " << node2->data << endl;;
}