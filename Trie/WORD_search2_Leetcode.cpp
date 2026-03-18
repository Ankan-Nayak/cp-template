class Solution {
public:
    struct Node {
        Node* links[26];
        string word = "";  // store word directly

        Node() {
            for (int i = 0; i < 26; i++)
                links[i] = nullptr;
        }
    };

    Node* root = new Node();

    void insert(string &word) {
        Node* node = root;
        for (char ch : word) {
            if (!node->links[ch - 'a'])
                node->links[ch - 'a'] = new Node();
            node = node->links[ch - 'a'];
        }
        node->word = word;  // mark complete word
    }

    int dx[4] = {-1, 1, 0, 0};
    int dy[4] = {0, 0, -1, 1};

    vector<string> ans;

    void dfs(vector<vector<char>>& board, int x, int y, Node* node) {
        char ch = board[x][y];

        if (ch == '#' || !node->links[ch - 'a'])
            return;

        node = node->links[ch - 'a'];

        // ✅ found word
        if (node->word != "") {
            ans.push_back(node->word);
            node->word = "";  // avoid duplicates
        }

        // mark visited
        board[x][y] = '#';

        for (int d = 0; d < 4; d++) {
            int nx = x + dx[d];
            int ny = y + dy[d];

            if (nx >= 0 && ny >= 0 && nx < board.size() && ny < board[0].size()) {
                dfs(board, nx, ny, node);
            }
        }

        // backtrack
        board[x][y] = ch;
    }

    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        // build trie
        for (auto &w : words)
            insert(w);

        for (int i = 0; i < board.size(); i++) {
            for (int j = 0; j < board[0].size(); j++) {
                dfs(board, i, j, root);
            }
        }

        return ans;
    }
};



/*_____________________________________________________________________________________________________________*/




class Solution {
public:
    int n, m;
    set<string> st;
    int dx[4] = {-1, 1, 0, 0};
    int dy[4] = {0, 0, -1, 1};

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

    void dfs(vector<vector<char>> &board, vector<vector<int>> &vis, Node* node, int x, int y, string cur) {
        char ch = board[x][y];
        if (!containsKey(node, ch)) return;
        node = get(node, ch);
        cur.push_back(ch);

        if (node->flag) {
            st.insert(cur);
        }

        vis[x][y] = 1;
        
        for (int d = 0; d < 4; ++d) {
            int nx = x + dx[d];
            int ny = y + dy[d];  // Fixed: was dx[d] instead of dy[d]
            
            // Check bounds and if it's a white cell
            if (nx >= 0 && ny >= 0 && nx < n && ny < m && vis[nx][ny] == 0) {
                dfs(board, vis, node, nx, ny, cur);
            }
        }
        vis[x][y] = 0; // backtrack
    }
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        n = board.size();
        m = board[0].size();

        for (auto &w : words) {
            insertWord(w);
        }

        vector<vector<int>> vis(n, vector<int> (m, 0));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                dfs(board, vis, root, i, j, "");
            }
        }

        vector<string> ans;
        for (auto it:st) {
            if (st.find(it) != st.end()) ans.push_back(it);
        }
        return ans;
    }
};