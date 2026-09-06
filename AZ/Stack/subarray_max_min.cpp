#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;
    vector<long long> A(n);
    for (int i = 0; i < n; i++) cin >> A[i];

    vector<int> prevGreater(n), nextGreaterEq(n);
    vector<int> prevSmaller(n), nextSmallerEq(n);
    stack<int> st;

    // prevGreater[i]: nearest index left, STRICTLY greater
    while (!st.empty()) st.pop();
    for (int i = 0; i < n; i++) {
        while (!st.empty() && A[st.top()] <= A[i]) st.pop();
        prevGreater[i] = st.empty() ? -1 : st.top();
        st.push(i);
    }
    // nextGreaterEq[i]: nearest index right, >= A[i]
    while (!st.empty()) st.pop();
    for (int i = n - 1; i >= 0; i--) {
        while (!st.empty() && A[st.top()] < A[i]) st.pop();
        nextGreaterEq[i] = st.empty() ? n : st.top();
        st.push(i);
    }
    // prevSmaller[i]: nearest index left, STRICTLY smaller
    while (!st.empty()) st.pop();
    for (int i = 0; i < n; i++) {
        while (!st.empty() && A[st.top()] >= A[i]) st.pop();
        prevSmaller[i] = st.empty() ? -1 : st.top();
        st.push(i);
    }
    // nextSmallerEq[i]: nearest index right, <= A[i]
    while (!st.empty()) st.pop();
    for (int i = n - 1; i >= 0; i--) {
        while (!st.empty() && A[st.top()] > A[i]) st.pop();
        nextSmallerEq[i] = st.empty() ? n : st.top();
        st.push(i);
    }

    __int128 sumMax = 0, sumMin = 0;

    for (int i = 0; i < n; i++) {
        long long leftMax  = i - prevGreater[i];         // # of valid start points
        long long rightMax = nextGreaterEq[i] - i;       // # of valid end points
        long long totalSubarraysAsMax = leftMax * rightMax;

        // subtract the 1 case where left=1,right=1 (the subarray is just [A[i]] alone, length 1)
        // that single length-1 case always exists exactly once (start=i, end=i)
        long long asMaxLenGE2 = totalSubarraysAsMax - 1;
        sumMax += (__int128)A[i] * asMaxLenGE2;

        long long leftMin  = i - prevSmaller[i];
        long long rightMin = nextSmallerEq[i] - i;
        long long totalSubarraysAsMin = leftMin * rightMin;

        long long asMinLenGE2 = totalSubarraysAsMin - 1;
        sumMin += (__int128)A[i] * asMinLenGE2;
    }

    long long sumMaxResult = (long long)sumMax;
    long long sumMinResult = (long long)sumMin;
    long long answer = sumMaxResult - sumMinResult;

    cout << "Sum of Max (length>=2 subarrays only): " << sumMaxResult << "\n";
    cout << "Sum of Min (length>=2 subarrays only): " << sumMinResult << "\n";
    cout << "Final Answer: " << answer << "\n";

    return 0;
}