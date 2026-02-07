class Solution {
public:
	ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
		ListNode *ptr1 = headA;
		ListNode *ptr2 = headB;
		while (ptr1 != ptr2) {
            if (ptr1 == NULL) {
                ptr1 = headB;
            }
            else {
                ptr1 = ptr1->next;
            }

            if (ptr2 == NULL) {
                ptr2 = headA;
            }
            else {
                ptr2 = ptr2->next;
            }
        }
        return ptr2;
	}
};

// or use diff of length start from the max len - diff pos


ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
    //Complete the function
    ListNode* ptr1 = headA;
    ListNode* ptr2 = headB;
    int countA = 0, countB = 0;
    while (ptr1) {
        ptr1 = ptr1->next;
        countA += 1;
    }
    while (ptr2) {
        ptr2 = ptr2->next;
        countB += 1;
    }
    int diff = abs(countA - countB);
    ptr1 = headA, ptr2 = headB;
    if (countA > countB) {
        while (diff--) ptr1 = ptr1->next;
    } else {
        while (diff--) ptr2 = ptr2->next;
    }

    while (ptr1 && ptr2) {
        if (ptr1 == ptr2) return ptr1;
        ptr1 = ptr1->next;
        ptr2 = ptr2->next;
    }
    return NULL;
}