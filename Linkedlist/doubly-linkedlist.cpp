#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* prev;
    Node* next;

    Node(int x) {
        data = x;
        prev = NULL;
        next = NULL;
    }
};

Node* head = NULL;

// Insert at front
void insertFront(int data) {
    Node* newNode = new Node(data);
    newNode->next = head;
    if (head != NULL)
        head->prev = newNode;
    head = newNode;
}

// Insert at end
void insertEnd(int data) {
    Node* newNode = new Node(data);
    if (head == NULL) {
        head = newNode;
        return;
    }
    Node* temp = head;
    while (temp->next != NULL)
        temp = temp->next;
    temp->next = newNode;
    newNode->prev = temp;
}

// Insert at position (1-based)
void insertAtPos(int data, int pos) {
    if (pos == 1) {
        insertFront(data);
        return;
    }

    Node* temp = head;
    for (int i = 1; temp != NULL && i < pos - 1; i++)
        temp = temp->next;

    if (temp == NULL) {
        cout << "Position out of bounds.\n";
        return;
    }

    Node* newNode = new Node(data);
    newNode->next = temp->next;
    newNode->prev = temp;

    if (temp->next != NULL)
        temp->next->prev = newNode;

    temp->next = newNode;
}

// Delete from front
void deleteFront() {
    if (head == NULL) return;

    Node* temp = head;
    head = head->next;
    if (head != NULL)
        head->prev = NULL;

    delete temp;
}

// Delete from end
void deleteEnd() {
    if (head == NULL) return;

    Node* temp = head;
    if (temp->next == NULL) {
        delete temp;
        head = NULL;
        return;
    }

    while (temp->next != NULL)
        temp = temp->next;

    temp->prev->next = NULL;
    delete temp;
}

// Delete at position
void deleteAtPos(int pos) {
    if (head == NULL) return;
    if (pos == 1) {
        deleteFront();
        return;
    }

    Node* temp = head;
    for (int i = 1; temp != NULL && i < pos; i++)
        temp = temp->next;

    if (temp == NULL) {
        cout << "Position out of bounds.\n";
        return;
    }

    if (temp->prev != NULL)
        temp->prev->next = temp->next;

    if (temp->next != NULL)
        temp->next->prev = temp->prev;

    delete temp;
}

// Print forward
void printForward() {
    Node* temp = head;
    cout << "Forward: ";
    while (temp != NULL) {
        cout << temp->data << " ";
        temp = temp->next;
    }
    cout << endl;
}

// Print backward
void printBackward() {
    Node* temp = head;
    if (!temp) return;
    while (temp->next != NULL)
        temp = temp->next;

    cout << "Backward: ";
    while (temp != NULL) {
        cout << temp->data << " ";
        temp = temp->prev;
    }
    cout << endl;
}

// Search
bool search(int val) {
    Node* temp = head;
    while (temp != NULL) {
        if (temp->data == val)
            return true;
        temp = temp->next;
    }
    return false;
}

// Length
int length() {
    int count = 0;
    Node* temp = head;
    while (temp != NULL) {
        count++;
        temp = temp->next;
    }
    return count;
}



int main() {
    insertEnd(10);
    insertFront(5);
    insertEnd(15);
    insertAtPos(12, 3);

    printForward();
    printBackward();

    deleteAtPos(2);
    printForward();

    cout << "Length: " << length() << endl;
    cout << "Search 15: " << (search(15) ? "Found" : "Not Found") << endl;

    return 0;
}
