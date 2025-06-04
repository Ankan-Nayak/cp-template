#include <bits/stdc++.h>
using namespace std;

// Tree node definition (similar to your LinkedList Node)
struct Node {
    int data;
    Node* left;
    Node* right;
    Node(int x) {
        data = x;
        left = right = NULL;
    }
};

// Helper function to perform preorder traversal
void preorderHelper(Node* root, vector<int>& preorder) {
    if (root == NULL) return;
    preorder.push_back(root->data);
    preorderHelper(root->left, preorder);
    preorderHelper(root->right, preorder);
}

// Main preorder traversal function
vector<int> preorderTraversal(Node* root) {
    vector<int> preorder;
    preorderHelper(root, preorder);
    return preorder;
}

// Driver code
int main() {
    // Example tree:
    //      1
    //       \
    //        2
    //       /
    //      3
    Node* root = new Node(1);
    root->right = new Node(2);
    root->right->left = new Node(3);

    vector<int> ans = preorderTraversal(root);
    for (int val : ans) {
        cout << val << " ";
    }
    cout << endl;

    return 0;
}
