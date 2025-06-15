#include <iostream>
#include <unordered_map>
#include <random>

using namespace std;

struct Node {
    int data = 0;
    Node * next = nullptr;
};

void printList(Node* &head) {
    Node* curr = head;
    while(curr != nullptr) {
        // cout << " -> " << curr->data << "{" << curr << "}" << "{next:" << curr->next << "}";
        cout << " -> " << curr->data;
        curr = curr->next;
    }
    cout << endl;
}

// O(N)
void removeDuplicates(Node* &head) {
    if(head == nullptr || head->next == nullptr) {
        return;
    }
    
    Node* curr = head;

    unordered_map<int, int>nodeSeen;

    while(curr != nullptr) {
        nodeSeen[curr->data]++;
        if (nodeSeen[curr->data] > 1){
            // remove from linked list
            if(!curr->next) { // if there is nothing to bump up to
                curr = nullptr;
            } else {
                curr->data = curr->next->data;
                curr->next = curr->next->next; // don't go to next, since this curr node is replaced and we need to look at this value now
            }
        } else {
            curr = curr->next;
        }
    }
}

// inserts at the start of the linked list
void insert(Node* &head, int data) {
    Node* newNode = new Node;
    newNode ->data = data;
    newNode->next = head;
    head = newNode;
}

int main() {
    Node* head = nullptr;
    for(int i = 0; i < 10; i++) {
        insert(head, rand() % 10);
    }

    cout << "=== original ===" << endl;
    printList(head);
    removeDuplicates(head);
    cout << "=== new ===" << endl;
    printList(head);

    Node* head2 = nullptr;
    for(int i = 0; i < 10; i++) {
        insert(head2, rand() % 10);
    }

    cout << "=== original ===" << endl;
    printList(head2);
    removeDuplicates(head2);
    cout << "=== new ===" << endl;
    printList(head2);
}