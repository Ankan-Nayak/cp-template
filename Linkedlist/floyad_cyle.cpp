ListNode* detectCycle(ListNode* head) {
    ListNode* slow = head;
    ListNode* fast = head;

    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) break;
    }

    if (!fast || !fast->next) return nullptr;

    slow = head;
    while (slow != fast) {
        slow = slow->next;
        fast = fast->next;
    }
    return slow;
}


// where the cycle starts

/* * * [*] * * * * *
        *        *
        *        *
        *  *  *  */


// head →──── L ────→ cycle start →── x ──→ meeting point
//                                ←── C ──→ (cycle)

// L = length from head to the start of cycle
// C = length of the cycle
// x = distance from cycle start to the meeting point
// slow moves 1 step at a time
// fast moves 2 steps at a time

// slow_distance = L + x + k1·C
// fast_distance = L + x + k2·C = 2 × slow_distance


// L + x + k₂·C = 2(L + x + k₁·C)
// k₂·C − 2k₁·C = L + x
// (k₂ − 2k₁) · C = L + x......if we do fast as 3 or other steps still (k₂ − nk₁) = K'..so same thing, we don't do, becuse it take more time to match slow = fast
// L + x = k · C
// L + x = k·C
// ⇒ L = k·C − x
// ⇒ L ≡ −x (mod C)
// ⇒ L ≡ C − x (mod C)



