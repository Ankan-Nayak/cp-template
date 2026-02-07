/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* next;
    Node* random;
    
    Node(int _val) {
        val = _val;
        next = NULL;
        random = NULL;
    }
};
*/

class Solution {
public:
    Node* copyRandomList(Node* head) {
        if (!head) return nullptr;

        Node* ptr = head;
        map<Node*, Node*> mp;

        while (ptr != NULL) {
            mp[ptr] = new Node(ptr->val);
            ptr = ptr->next;
        }

        ptr = head;
        while (ptr != NULL) {
            mp[ptr]->next = mp[ptr->next];
            mp[ptr]->random = mp[ptr->random];
            ptr = ptr->next;
        }

        return mp[head];
    }
}; 
// TC - 0(NlogN), SC - 0(N)




class Solution {
public:
    Node* copyRandomList(Node* head) {
        if (!head) return nullptr;

        Node* curr = head;

        // 🔹 Step 1: Insert copy nodes after original nodes
        while (curr) {
            Node* copy = new Node(curr->val);
            copy->next = curr->next;
            curr->next = copy;
            curr = copy->next;
        }

        // 🔹 Step 2: Assign random pointers to copied nodes
        curr = head;
        while (curr) {
            if (curr->random)
                curr->next->random = curr->random->next;
            curr = curr->next->next;
        }

        // 🔹 Step 3: Separate original and copied lists
        curr = head;
        Node* copyHead = head->next;
        Node* copyCurr = copyHead;

        while (curr) {
            curr->next = copyCurr->next;
            curr = curr->next;

            if (curr) {
                copyCurr->next = curr->next;
                copyCurr = copyCurr->next;
            }
        }

        return copyHead;
    }
};

// TC - 0(N), SC - 0(1)
// why 0(1) not 0(N)
// 1️⃣ Output space (MANDATORY)
// Space required to store the result
// This is not counted

// 2️⃣ Extra / auxiliary space (OPTIONAL)
// HashMaps, arrays, stacks, recursion memory, etc.
// This is counted


// Before:
// 1 ----> 2 ----> 3 ----> NULL
// |       |       |
// v       v       v
// 3       1       2


// After inserting copies:

// 1 ---> 1' ---> 2 ---> 2' ---> 3 ---> 3' ---> NULL
// |        |       |        |       |        |
// v        v       v        v       v        v
// 3        ?       1        ?       2        ?


// 1 ---> 1' ---> 2 ---> 2' ---> 3 ---> 3'
// |        |       |        |       |        |
// v        v       v        v       v        v
// 3        3'      1        1'      2        2'


// Original list:
// 1 → 2 → 3 → NULL
// |    |    |
// v    v    v
// 3    1    2


// Copied list:
// 1' → 2' → 3' → NULL
// |     |     |
// v     v     v
// 3'    1'    2'
