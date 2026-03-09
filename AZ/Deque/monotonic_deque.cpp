// Approach
// I switched to a Monotonic Deque strategy. Basically, I use a deque to keep track of indices, making sure the values they point to are always in decreasing order.

// Cleaning from the back: Whenever I see a new number, I compare it to the numbers at the back of my deque. If the new number is bigger, the old ones are useless (they'll never be the maximum again), so I pop them out.
// Adding the new guy: I push the current index into the deque.
// Checking the front: If the index at the front of my deque is too old (it fell out of the window), I toss it.
// Grabbing the answer: After the first window is set up, the front of my deque is always the index of the largest number for that window.
// Let’s use the example: arr = [1, 3, -1, -3] with k = 3.

// Step 1 (i = 0, val = 1): The deque is empty, so we just add the index 0.
// Step 2 (i = 1, val = 3): Before adding 3, we look at the back of the deque. Since 3 is bigger than the value at index 0 (which is 1), the 1 is now useless. We pop index 0 and push index 1.
// Step 3 (i = 2, val = -1): We compare -1 to the back (index 1, value 3). Since -1 is smaller, we keep 3 and just push index 2 behind it. Now that our window has 3 elements, we look at the front of the deque. The value at index 1 is 3, so our first answer is 3.
// Step 4 (i = 3, val = -3): We compare -3 to the back (index 2, value -1). It’s smaller, so we just push index 3 to the back. We check if the front (index 1) is out of range. It’s not (index 1 is still within the last 3 spots). The front is still index 1, so our next answer is 3
// Basically, the deque always keeps the "biggest" index at the front, and any time a new big number shows up, it kicks out all the smaller numbers at the back because they'll never be the "max" again!

// Complexity
// Time complexity:O(n). Even though there’s a loop inside a loop, every element is only pushed and popped from the deque once. It’s super fast compared to my old O(n×k) way

// Space complexity: O(k).The deque only ever holds indices that are within the current window size.

// Code
class Solution {
  public:
    vector<int> maxSlidingWindow(vector<int>& arr, int k) {
        int n=arr.size();
        vector<int>ans;
        deque<int>dq;//we'll store indexes HERE
        for(int i=0;i<n;i++){
            while(!dq.empty() && arr[dq.back()]<=arr[i]){
                dq.pop_back();
            }
            dq.push_back(i);
            if(dq.front()==i-k){
                dq.pop_front();
            }
            if(i>=k-1){
                ans.push_back(arr[dq.front()]);
            }
        }
        return ans;
    }
};