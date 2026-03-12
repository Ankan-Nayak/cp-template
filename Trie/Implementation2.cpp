#include <bits/stdc++.h>
using namespace std;

struct Node {
    Node* links[26];
    bool flag;
    int cntEndWith;
    int cntPrefix;

    Node() {
        flag = false;
        cntEndWith = 0;
        cntPrefix = 0;
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

void insertWord(string word) {
    Node* node = root;

    for (char ch : word) {
        if (!containsKey(node, ch)) {
            put(node, ch);
        }

        node = get(node, ch);
        node->cntPrefix++;
    }

    node->cntEndWith++;
    node->flag = true;
}

bool searchWord(string word) {
    Node* node = root;

    for (char ch : word) {
        if (!containsKey(node, ch))
            return false;

        node = get(node, ch);
    }

    return node->flag;
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

int countWordsEqualTo(string word) {
    Node* node = root;

    for (char ch : word) {
        if (!containsKey(node, ch))
            return 0;

        node = get(node, ch);
    }

    return node->cntEndWith;
}

int countWordsStartingWith(string prefix) {
    Node* node = root;

    for (char ch : prefix) {
        if (!containsKey(node, ch))
            return 0;

        node = get(node, ch);
    }

    return node->cntPrefix;
}

void eraseWord(string word) {
    Node* node = root;

    for (char ch : word) {
        if (!containsKey(node, ch))
            return;

        node = get(node, ch);
        node->cntPrefix--;
    }

    node->cntEndWith--;
}

int main() {

    cout << "Basic Trie operations\n";

    insertWord("apple");

    cout << "Search apple: " << searchWord("apple") << endl;
    cout << "Search app: " << searchWord("app") << endl;
    cout << "StartsWith app: " << startsWithPrefix("app") << endl;

    insertWord("app");

    cout << "Search app: " << searchWord("app") << endl;

    cout << "\nAdvanced Trie operations\n";

    insertWord("apple");
    insertWord("apple");

    cout << "Count Words Equal To apple: ";
    cout << countWordsEqualTo("apple") << endl;

    cout << "Count Words Starting With app: ";
    cout << countWordsStartingWith("app") << endl;

    cout << "Erasing apple\n";
    eraseWord("apple");

    cout << "Count Words Equal To apple: ";
    cout << countWordsEqualTo("apple") << endl;

    cout << "Count Words Starting With app: ";
    cout << countWordsStartingWith("app") << endl;

    cout << "Erasing apple\n";
    eraseWord("apple");

    cout << "Count Words Starting With app: ";
    cout << countWordsStartingWith("app") << endl;

    return 0;
}

// if word was before, so that decide earse or not -> store "words" in <MAP> and check