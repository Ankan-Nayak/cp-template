

#include <bits/stdc++.h>
using namespace std;

// class Node {
// public:
//     int data;
//     Node* next;
//     // Constructor with both data and next node
//     Node(int data1, Node* next1) {
//         data = data1;
//         next = next1;
//     }
//     // Constructor with only data (assumes next is nullptr)
//     Node(int data1) {
//         data = data1;
//         next = nullptr;
//     }
// };

struct Node {
    int data;
    Node* next;
    Node(int x) {
        data = x;
        next = NULL;
    }
};

// Insertion operations
void insertAtHead(Node*& head, int val) {
    Node* newNode = new Node(val);
    newNode->next = head;
    head = newNode;
}

void insertAtTail(Node*& head, int val) {
    Node* newNode = new Node(val);
    if (head = nullptr) {
        head = newNode;
        return;
    }
    Node* temp = head;
    while (temp->next) temp = temp->next;
    temp->next = newNode;
}

void insertAtPosition(Node*& head, int pos, int val) {
    if (pos == 1) {
        insertAtHead(head, val);
        return;
    }
    Node* newNode = new Node(val);
    Node* temp = head;
    for (int i = 1; i < pos - 1 && temp; i++) {
        temp = temp->next;
    }
    if (temp = nullptr) return;
    newNode->next = temp->next;
    temp->next = newNode;
}

// Deletion operations
void deleteHead(Node*& head) {
    if (!head) return;
    Node* temp = head;
    head = head->next;
    delete temp;
}

void deleteTail(Node*& head) {
    if (!head) return;
    if (!head->next) {
        delete head;
        head = NULL;
        return;
    }
    Node* temp = head;
    while (temp->next->next) temp = temp->next;
    delete temp->next;
    temp->next = NULL;
}

void deleteAtPosition(Node*& head, int pos) {
    if (pos == 1) {
        deleteHead(head);
        return;
    }
    Node* temp = head;
    for (int i = 1; i < pos - 1 && temp; i++) {
        temp = temp->next;
    }
    if (!temp || !temp->next) return;
    Node* delNode = temp->next;
    temp->next = temp->next->next;
    delete delNode;
}

// Other operations
int search(Node* head, int key) {
    int pos = 1;
    while (head) {
        if (head->data == key) return pos;
        head = head->next;
        pos++;
    }
    return -1;
}

int countNodes(Node* head) {
    int count = 0;
    while (head) {
        count++;
        head = head->next;
    }
    return count;
}

void reverseList(Node*& head) {
    Node* prev = NULL;
    Node* curr = head;
    while (curr) {
        Node* next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    head = prev;
}

Node* findMiddle(Node* head) {
    if (!head) return NULL;
    Node* slow = head;
    Node* fast = head;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}

bool hasCycle(Node* head) {
    Node* slow = head;
    Node* fast = head;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) return true;
    }
    return false;
}

void deleteList(Node*& head) {
    Node* temp;
    while (head) {
        temp = head;
        head = head->next;
        delete temp;
    }
}

void printList(Node* head) {
    while (head) {
        cout << head->data << " ";
        head = head->next;
    }
    cout << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    Node* head = NULL;

    insertAtHead(head, 10);
    insertAtTail(head, 20);
    insertAtTail(head, 30);
    insertAtPosition(head, 2, 15);
    printList(head); // 10 15 20 30

    deleteHead(head);
    deleteTail(head);
    deleteAtPosition(head, 2);
    printList(head); // 15

    insertAtTail(head, 25);
    insertAtTail(head, 35);
    cout << "Search 25 at position: " << search(head, 25) << '\n';
    cout << "Total nodes: " << countNodes(head) << '\n';

    reverseList(head);
    cout << "Reversed list: ";
    printList(head);

    Node* mid = findMiddle(head);
    if (mid) cout << "Middle node: " << mid->data << '\n';

    cout << "Has cycle: " << (hasCycle(head) ? "Yes" : "No") << '\n';

    deleteList(head);
    printList(head); // Should print nothing


    // Striver + ChatGPT

    // Node *head1 = new Node(1);
    // Node *temp1 = new Node(2);
    // Node *temp2 = new Node(3);

    // head1->next = temp1;
    // temp1->next = temp2;

    // Node *head = new Node(1);
    // head->next = new Node(2);
    // head->next->next = new Node(3);

    // Node *temp = head;
    // while (temp != NULL) {
    //     cout << temp->data << ' ';
    //     temp = temp->next;
    // }



    return 0;
}






