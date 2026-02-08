#include <bits/stdc++.h>
using namespace std;

/* ---------------- NODE DEFINITION ---------------- */
struct Node {
    int data;
    Node* npx;   // XOR of prev and next
};

/* ---------------- XOR HELPER ---------------- */
Node* XOR(Node* a, Node* b) {
    return (Node*)((uintptr_t)(a) ^ (uintptr_t)(b));
}

/* ---------------- INSERT AT POSITION ---------------- */
/*
    pos = 1  → insert at head
    pos = n+1 → insert at tail
*/
void insertAtPos(Node*& head, Node*& tail, int val, int pos) {
    Node* newNode = new Node{val, nullptr};

    // Empty list
    if (!head) {
        head = tail = newNode;
        return;
    }

    // Insert at head
    if (pos == 1) {
        newNode->npx = XOR(nullptr, head);
        Node* next = XOR(nullptr, head->npx);
        head->npx = XOR(newNode, next);
        head = newNode;
        return;
    }

    Node* curr = head;
    Node* prev = nullptr;
    Node* next;
    int count = 1;

    while (curr && count < pos - 1) {
        next = XOR(prev, curr->npx);
        prev = curr;
        curr = next;
        count++;
    }

    // Insert at tail
    if (!curr) {
        newNode->npx = XOR(tail, nullptr);
        Node* prevTail = XOR(tail->npx, nullptr);
        tail->npx = XOR(prevTail, newNode);
        tail = newNode;
        return;
    }

    // Insert in middle
    next = XOR(prev, curr->npx);
    newNode->npx = XOR(curr, next);
    curr->npx = XOR(prev, newNode);
    if (next)
        next->npx = XOR(newNode, XOR(curr, next->npx));
}

/* ---------------- DELETE AT POSITION ---------------- */
void deleteAtPos(Node*& head, Node*& tail, int pos) {
    if (!head) return;

    Node* curr = head;
    Node* prev = nullptr;
    Node* next;
    int count = 1;

    // Delete head
    if (pos == 1) {
        next = XOR(nullptr, head->npx);
        if (next)
            next->npx = XOR(nullptr, XOR(head, next->npx));
        else
            tail = nullptr;

        delete head;
        head = next;
        return;
    }

    while (curr && count < pos) {
        next = XOR(prev, curr->npx);
        prev = curr;
        curr = next;
        count++;
    }

    if (!curr) return;

    next = XOR(prev, curr->npx);

    if (next)
        next->npx = XOR(prev, XOR(next->npx, curr));
    else
        tail = prev;

    prev->npx = XOR(XOR(prev->npx, curr), next);

    delete curr;
}

/* ---------------- DISPLAY ---------------- */
void display(Node* head) {
    Node* curr = head;
    Node* prev = nullptr;
    Node* next;

    while (curr) {
        cout << curr->data << " ";
        next = XOR(prev, curr->npx);
        prev = curr;
        curr = next;
    }
    cout << endl;
}

/* ---------------- REVERSE LIST ---------------- */
/*
    No pointer updates needed
*/
void reverseList(Node*& head, Node*& tail) {
    swap(head, tail);
}

/* ---------------- SECTIONAL REVERSE ---------------- */
void sectionalReverse(Node*& head, Node*& tail, int L, int R) {
    if (L >= R || !head) return;

    vector<Node*> v;
    Node* curr = head;
    Node* prev = nullptr;
    Node* next;

    while (curr) {
        v.push_back(curr);
        next = XOR(prev, curr->npx);
        prev = curr;
        curr = next;
    }

    reverse(v.begin() + L - 1, v.begin() + R);

    int n = v.size();
    for (int i = 0; i < n; i++) {
        Node* p = (i == 0) ? nullptr : v[i - 1];
        Node* nx = (i == n - 1) ? nullptr : v[i + 1];
        v[i]->npx = XOR(p, nx);
    }

    head = v[0];
    tail = v[n - 1];
}

/* ---------------- MAIN ---------------- */
int main() {
    Node* head = nullptr;
    Node* tail = nullptr;

    insertAtPos(head, tail, 1, 1);
    insertAtPos(head, tail, 2, 2);
    insertAtPos(head, tail, 3, 3);
    insertAtPos(head, tail, 4, 4);
    insertAtPos(head, tail, 5, 5);

    display(head);   // 1 2 3 4 5

    insertAtPos(head, tail, 99, 3);
    display(head);   // 1 2 99 3 4 5

    deleteAtPos(head, tail, 4);
    display(head);   // 1 2 99 4 5

    reverseList(head, tail);
    display(head);   // 5 4 99 2 1

    sectionalReverse(head, tail, 2, 4);
    display(head);   // 5 2 99 4 1
}

// do operation on 0(1)