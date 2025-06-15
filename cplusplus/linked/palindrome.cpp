#include <iostream>
#include <random>
#include <stack>

// approach 1: reverse half of the list and compare it with the other half
// approach 2: iterate
// approach 3: recursive

// check if list is palindrome

using namespace std;

struct Node {
    char data;
    Node *next;
    Node(char c): data{c}, next{nullptr} {}
};

void insert(Node * &head, char c) {
    Node * newNode = new Node(c);
    newNode->next = head;
    head = newNode;
}

void printList(Node *head) {
    while(head != nullptr) {
        cout << head->data << "->";
        head = head->next;
    }
    cout << endl;
}


void reverse(Node * &head) {
    if(head == nullptr || (head && (head->next == nullptr))) {
        return;
    }
    Node * newHead = nullptr;
    Node * nextNode = nullptr;
    while(head) {
        // [a][b][c]            newHead = null
        // a->next = null, newHead = a, head = b
        // b->next = a, newHead = b, head = c
        // c->next = b, newHead = c, head = nullptr
        // (break)
        // c->b->a

        // take the next node after head
        // and put it to the front
        // move to next, and put this next node to the front, so on.
        nextNode = head->next;
        head->next = newHead; // this head's next becomes the "new head" from the last iteration
        newHead = head;       // the "new head" becomes this head
        head = nextNode;      // proceed to the next node
        
    }
    head = newHead;
}

bool isPalindromeIter1(Node * head) {
    // if list is empty or just contains one node
    if(head == nullptr || head->next == nullptr) {
        return true;
    }

    // find the middle node
    Node * ptr1 = head;
    Node * ptr2 = head;
    Node * middleNode = nullptr;


    // [1][][][][][]
    // [2][][][][][]

    // [][][1][][][]
    // [][2][][][][]

    // [][][][][1][] <- if this were len 5, then would stop here, and [2] would be bumped up one
    // [][][2][][][]

    // [][][][][][] 1
    // [][][][2][][]
    while(ptr2 && ptr1 && ptr1->next) {
        ptr1 = ptr1->next->next;
        ptr2 = ptr2->next;
    }

    // in case of odd number of nodes,
    // skip the middle one
    if(ptr1 && ptr1->next == nullptr) {
        ptr2 = ptr2->next;
    }

    // reversing (using ptr2 to split off a new list)
    reverse(ptr2);

    // compare the two halves
    middleNode = ptr2;
    ptr1 = head;

    while(ptr1 && ptr2 && ptr1->data == ptr2->data) {
        ptr1 = ptr1->next;
        ptr2 = ptr2->next;
    }

    // reverse the list again to restore original
    reverse(middleNode);

    // if we iterated to the very end, this was a palindrome
    // (not using ptr1, because ptr1->next will be not null)
    if (ptr2 == nullptr) {
        return true;
    }

    return false;
}

bool IsPalindromeIter2(Node * head) {
    if(head == nullptr || (head && head->next == nullptr)) {
        return true;
    }

    Node * ptr1 = head;
    Node * ptr2 = head;

    stack<Node*> nodeStack;

    // push the first half of the list onto the stack
    while(ptr2 && ptr1 && ptr1->next) {
        ptr1 = ptr1->next->next;
        nodeStack.push(ptr2);
        ptr2 = ptr2->next;
    }

    // in case of odd len, skip the middle node (altogether, this could be unique, it doesn't matter)
    if(ptr1 && ptr1->next == nullptr) {
        ptr2 = ptr2->next;
    }

    // fifo stack, so pops out in reverse order
    while(!nodeStack.empty() && ptr2) {
        Node * curr = nodeStack.top();
        nodeStack.pop();
        if(curr->data != ptr2->data) {
            return false;
        }
        ptr2 = ptr2->next;
    }

    return true;
}

// [LR][][][][][]
// [L][][][][][] R
// [L][][][][][R]
// [][L][][R][][]
// [][][LR][][][] // <-- technically you might be able to stop here...
// [][LR][][][][]
// [LR][][][][][]
bool isPalindromeRecur(Node * &left, Node *right) {
    // base case is to stop when right becomes nullptr
    if(right == nullptr) {
        return true;
    }

    bool isP = isPalindromeRecur(left, right->next);
    if(!isP) {
        return false;
    }

    isP = (left->data == right->data);

    // move left for the next call
    left = left->next;

    return isP;
}

bool isPalindromeRecurH(Node * head) {
    return isPalindromeRecur(head, head);
}

int main() {
    Node * head1 = nullptr;
    insert(head1, 'a');
    insert(head1, 'b');
    insert(head1, 'c');
    insert(head1, 'c');
    insert(head1, 'b');
    insert(head1, 'a');

    //printList(head1);
    cout << boolalpha << isPalindromeIter1(head1) << endl;
    //printList(head1);4
    cout << boolalpha << IsPalindromeIter2(head1) << endl;
    //printList(head1);
    cout << boolalpha << isPalindromeRecurH(head1) << endl;
    printList(head1);
}