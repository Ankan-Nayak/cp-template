#include <bits/stdc++.h>
using namespace std;

struct Node {
    Node* links[26];
    bool flag;

    Node() {
        flag = false;
        for (int i = 0; i < 26; i++)
            links[i] = nullptr;
    }
};

Node* root = new Node();

bool containsKey(Node* node, char ch) {
    return node->links[ch - 'a'] != nullptr;
}

Node* get(Node* node, char ch) {
    return node->links[ch - 'a'];
}

void put(Node* node, char ch) {
    node->links[ch - 'a'] = new Node();
}

void setEnd(Node* node) {
    node->flag = true;
}

bool isEnd(Node* node) {
    return node->flag;
}

void insertWord(string word) {
    Node* node = root;

    for (char ch : word) {
        if (!containsKey(node, ch)) {
            put(node, ch);
        }
        node = get(node, ch);
    }

    setEnd(node);
}

bool searchWord(string word) {
    Node* node = root;

    for (char ch : word) {
        if (!containsKey(node, ch))
            return false;

        node = get(node, ch);
    }

    return isEnd(node);
}

bool startsWithPrefix(string prefix) {
    Node* node = root;

    for (char ch : prefix) {
        if (!containsKey(node, ch))
            return false;

        node = get(node, ch);
    }

    return true;
}

int main() {

    vector<string> operations = {
        "Trie","insert","search","search","startsWith","insert","search"
    };

    vector<vector<string>> arguments = {
        {},
        {"apple"},
        {"apple"},
        {"app"},
        {"app"},
        {"app"},
        {"app"}
    };

    vector<string> output;

    for (int i = 0; i < operations.size(); i++) {

        if (operations[i] == "Trie") {
            root = new Node();
            output.push_back("null");
        }

        else if (operations[i] == "insert") {
            insertWord(arguments[i][0]);
            output.push_back("null");
        }

        else if (operations[i] == "search") {
            bool result = searchWord(arguments[i][0]);
            output.push_back(result ? "true" : "false");
        }

        else if (operations[i] == "startsWith") {
            bool result = startsWithPrefix(arguments[i][0]);
            output.push_back(result ? "true" : "false");
        }
    }

    for (string res : output) {
        cout << res << endl;
    }

    return 0;
} 