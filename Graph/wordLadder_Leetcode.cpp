#include <bits/stdc++.h>
using namespace std;

const int N = 1e5+10;
set<string> wordList;

map<string, int> vis;
map<string, int> level;
vector<int> parent(N, -1);

string beginWord, endWord;


void bfs(string source) {
    queue<string> q;
    q.push(source);
    vis[source] = 1;
    level[source] = 1;

    while(!q.empty()) {
        string curr_v = q.front();
        q.pop();

        string temp;
        // for all postion of word[0,1,2..L-1]
        for (int i = 0; i < curr_v.size(); ++i) {
            temp = curr_v;

            // try changing letter in single position, try with s[i] = 'a' / 'b'..'z'
            for (char ch = 'a'; ch <= 'z'; ++ch) {
                if (ch == curr_v[i]) continue;

                temp[i] = ch;
                if (wordList.find(temp) != wordList.end()) {
                    if (!vis[temp]) {
                        q.push(temp);
                        vis[temp] = 1;
                        level[temp] = level[curr_v] + 1; 
                        // base case
                        if (vis[endWord]) return;
                    }
                }
            }
        }
    }
}


signed main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
   
    cin >> beginWord >> endWord;
    int sz = beginWord.size();

    for (int i = 0; i < 5; ++i) {
        string s;
        cin >> s;
        if (s.size() == sz) wordList.insert(s);
    }

    // bfs like Rubiks Cube project
    // each string is a node
    bfs(beginWord);
    cout << level[endWord] << endl;

    for (auto it : wordList) {
        cout << it << ' ' << level[it] << endl;
    }
}

// give shortest path from root(beginWord) to dest(endWord)

// Space Complexity 0(N)
// Time Complexity 0(L * 26 * logN * N)
// N is for no of nodes. for each Node (L * 26 * logN)