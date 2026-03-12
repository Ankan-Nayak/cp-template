class TrieNode {
public:
    bool flag;
    map<char, TrieNode*> children;

    TrieNode() {
        flag = false;
    }
};

class WordDictionary {
    TrieNode* root;
public:
    WordDictionary() {
        root = new TrieNode();
    }
    
    void addWord(string word) {
        TrieNode* node = root;
        for (char ch : word) {
            if (node->children.find(ch) == node->children.end()) {
                node->children[ch] = new TrieNode();
            }
            node = node->children[ch];
        }
        node->flag = true;
    }
    
    bool search(string word) {
        return searchHelp(root, word, 0);
    }
    bool searchHelp(TrieNode* node, string word, int len) {
        if (len == word.size()) {
            return node->flag;
        }
        char ch = word[len];
        if (ch != '.') {
            if (node->children.find(ch) == node->children.end()) return false;
            node = node->children[ch];
            return searchHelp(node, word, len + 1);
        }
        else {
            for (auto &p : node->children) {
                if (searchHelp(p.second, word, len + 1)) return true;
            }
            return false;
        }
    }
};

/**
 * Your WordDictionary object will be instantiated and called as such:
 * WordDictionary* obj = new WordDictionary();
 * obj->addWord(word);
 * bool param_2 = obj->search(word);
 */