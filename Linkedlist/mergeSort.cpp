ListNode* getMiddle(ListNode* head) {
    ListNode* slow = head;
    ListNode* fast = head->next; // for 1->2->NULL otherwise inf loop call
    while(fast  &&  fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}

ListNode* merge(ListNode* l1, ListNode* l2) {
    if (l1 == nullptr) return l2;
    if (l2 == nullptr) return l1;

    if (l1->val <= l2->val) {
        l1->next = merge(l1->next, l2);
        return l1;
    } else {
        l2->next = merge(l1, l2->next);
        return l2;
    }
}

ListNode* mergesort(ListNode* head) {
    //Complete the function
    if (!head  ||  !head->next) return head;

    ListNode* mid = getMiddle(head);
    ListNode* right = mid->next;
    mid->next = nullptr;

    ListNode* leftSorted = mergesort(head);
    ListNode* rightSorted = mergesort(right);

    return merge(leftSorted, rightSorted);
}