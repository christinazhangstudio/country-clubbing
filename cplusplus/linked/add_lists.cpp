#include <iostream>
#include <random>

// two numbers in which digits are stored in reverse order of linked list
// 617 + 295 = 912
// 7->1->6 5->9->2 = 2->1->9

using namespace std;

struct Node {
    int data;
    Node * next;
    Node(int d): data{d}, next{nullptr} {};
};


void insert(Node* &head, int data) {
    Node* newNode = new Node(data);
    newNode->next = head;
    head = newNode;
}

void insertFromBack(Node * &head, int data) {
    Node *newNode = new Node(data);
    
    if (head == nullptr) {
        head = newNode;
    } else {
        Node *last = head;
        while(last->next != nullptr) {
            last = last->next;
        }
    
        last->next = newNode;
    }
}

Node* addLists(Node *num1, Node *num2) {
    Node *sumList = nullptr;
    int carry = 0;

    while(num1 != nullptr && num2 != nullptr) {
        int sum = num1->data + num2->data + carry;
        // 11 -> 1 with carry to right 1
        // 9 + 9 = 18 -> 8 with carry to right 1
        // 2 -> 2, 0 carry
        carry = (sum > 9) ? 1 : 0;
        int newNum = sum % 10;
        
        insertFromBack(sumList, newNum);

        num1 = num1->next;
        num2 = num2->next;
    }

    return sumList;
}


void printList(Node *head) {
    while(head != nullptr) {
        cout << head->data << "->";
        head = head->next;
    }
    cout << endl;
}

int main() {
    Node *num1 = nullptr;
    insert(num1, 6);
    insert(num1, 1);
    insert(num1, 7);

    printList(num1);
    
    Node *num2 = nullptr;
    insert(num2, 2);
    insert(num2, 9);
    insert(num2, 5);

    printList(num2);

    printList(addLists(num1, num2));
}
