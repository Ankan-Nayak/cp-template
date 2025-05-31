
// Case 1: ListNode dummy; (stack)
// ListNode dummy;
// dummy is an actual ListNode object stored on the stack.

// It stores:

// dummy.val → initialized to 0 (default constructor)

// dummy.next → initially nullptr

// It's a real object, not a pointer.



/*-------------------------------------------------------------------------------------------------------------------------------------*/




// Case 2: ListNode* dummy = new ListNode(); (heap)

// ListNode* dummy = new ListNode();
// dummy is a pointer that stores the memory address of a ListNode object created on the heap.

// What dummy itself stores: a memory address like 0x7ffdf230abcd

// What the pointed-to node stores:

// dummy->val → 0

// dummy->next → nullptr


/*-------------------------------------------------------------------------------------------------------------------------------------*/



🧠 Key Point: Dot (.) vs Arrow (->)
Syntax	Used with	Meaning
dummy.next	An object	Access member of an object directly
dummy->next	A pointer	Access member of object via pointer

🔍 Scenario 1: ListNode dummy; (object)

ListNode dummy;
dummy.next = new ListNode(5); // connect a real node






/*-------------------------------------------------------------------------------------------------------------------------------------*/


class Solution {
public:
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        ListNode* ptr = new ListNode(); // dummy node
        ListNode* tail = ptr;

        while (list1 != nullptr && list2 != nullptr) {
            if (list1->val >= list2->val) {
                tail->next = list2;
                list2 = list2->next;
            } else {
                tail->next = list1;
                list1 = list1->next;
            }
            tail = tail->next; // ✅ move tail forward
        }

        // Append remaining nodes
        if (list1 == nullptr) tail->next = list2;
        else tail->next = list1;

        return ptr->next; // skip the dummy node
    }
};



/*-------------------------------------------------------------------------------------------------------------------------------------*/


class Solution {
public:
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        ListNode dummy; // dummy node to simplify logic
        ListNode* tail = &dummy; // tail points to the last node in the merged list

        while (list1 != nullptr && list2 != nullptr) {
            if (list1->val <= list2->val) {
                tail->next = list1;
                list1 = list1->next;
            } else {
                tail->next = list2;
                list2 = list2->next;
            }
            tail = tail->next; // advance the tail
        }

        // One list might still have remaining nodes
        if (list1 != nullptr) tail->next = list1;
        else tail->next = list2;

        return dummy.next; // first real node of merged list
    }
};
