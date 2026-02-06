
#include <bits/stdc++.h>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};


ListNode* addTwoNumbers(ListNode* n1, ListNode* n2) {
    //Complete the function
    int c1 = 0, c2 = 0;
    ListNode* head1 = n1;
    ListNode* head2 = n2;
    while (head1) {
        c1 += 1;
        head1 = head1->next;
    }
    while (head2) {
        c2 += 1;
        head2 = head2->next;
    }

    if (c1 < c2) {
        swap(n1, n2);
    } 
    head1 = n1;
    head2 = n2;
    
    int temp = 0;
    while (head1) {
        temp = head1->val + temp;
        if (head2) temp += head2->val;

        if (temp >= 10) {
            head1->val = temp % 10;
            temp = 1;
        } else {
            head1->val = temp % 10;
            temp = 0;
        }
        if (head1->next == nullptr  &&  temp == 1) {
            ListNode* newNode = new ListNode(1);
            head1->next = newNode;
            break;
        }
        head1 = head1->next;
        if (head2) head2 = head2->next;
    }

    return n1;
}


ListNode* GetList(string &num) {
    ListNode* n1 = nullptr;
    ListNode* head = nullptr;
    for(int i = (int)num.length() - 1; i >= 0; i--) {
        ListNode* temp = new ListNode(num[i] - '0');
        if(n1) {
            n1->next = temp;
            n1 = temp;
        }
        else {
            n1 = temp;
            head = n1;
        }
    }
    return head;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    string num1, num2;
    cin >> num1;
    cin >> num2;

    ListNode* n1 = GetList(num1);
    ListNode* n2 = GetList(num2);

    ListNode* sum = addTwoNumbers(n1, n2);

    string ans = "";
    while(sum) {
        ans += ('0' + sum->val);
        sum = sum->next;
    }

    reverse(ans.begin(), ans.end());

    cout << ans << "\n";

    return 0;
}
