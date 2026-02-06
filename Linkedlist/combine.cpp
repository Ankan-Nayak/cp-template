#include <bits/stdc++.h>
using namespace std;

struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(NULL) {}
};

/* Reverse a linked list */
ListNode* reverseList(ListNode* head) {
    ListNode* prev = NULL;
    ListNode* curr = head;
    while (curr) {
        ListNode* next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    return prev;
}

/* Find middle of linked list */
ListNode* middleNode(ListNode* head) {
    ListNode* slow = head;
    ListNode* fast = head;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}

/* Reorder list: a1 → an → a2 → an-1 → ... */
void reorderList(ListNode* head) {
    if (!head || !head->next) return;

    // 1. Find middle
    ListNode* mid = middleNode(head);

    // 2. Split list
    ListNode* second = mid->next;
    mid->next = NULL;   // important: end first half

    // 3. Reverse second half
    second = reverseList(second);

    // 4. Merge alternately
    ListNode* first = head;
    while (second) {
        ListNode* t1 = first->next;
        ListNode* t2 = second->next;

        first->next = second;
        second->next = t1;

        first = t1;
        second = t2;
    }
}

/* Utility: build list from vector */
ListNode* buildList(const vector<int>& v) {
    ListNode* head = NULL;
    ListNode* tail = NULL;
    for (int x : v) {
        if (!head) {
            head = tail = new ListNode(x);
        } else {
            tail->next = new ListNode(x);
            tail = tail->next;
        }
    }
    return head;
}

/* 🔥 UNREORDER (restore original list) */
void unreorderList(ListNode* head) {
    if (!head || !head->next) return;

    ListNode* first = head;
    ListNode* second = head->next;

    ListNode* head1 = first;
    ListNode* head2 = second;

    // 1️⃣ Separate alternating nodes
    while (second && second->next) {
        first->next = second->next;
        first = first->next;

        second->next = first->next;
        second = second->next;
    }
    first->next = NULL;

    // 2️⃣ Reverse second list
    head2 = reverseList(head2);

    // 3️⃣ Attach second list at end of first
    first = head1;
    while (first->next) first = first->next;
    first->next = head2;
}


/* Utility: print list */
void printList(ListNode* head) {
    while (head) {
        cout << head->val << " ";
        head = head->next;
    }
    cout << "\n";
}

int main() {
    int n;
    cin >> n;

    vector<int> v(n);
    for (int i = 0; i < n; i++) {
        cin >> v[i];
    }

    ListNode* head = buildList(v);

    reorderList(head);

    printList(head);

    return 0;
}
