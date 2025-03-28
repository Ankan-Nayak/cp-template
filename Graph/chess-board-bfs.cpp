#include <bits/stdc++.h>
using namespace std;

const int inf = 1e9+10;

int vis[8][8];
int level[8][8];

bool isValid(int x, int y) {
    return x >= 0  &&  y >= 0  &&  x < 8  &&  y < 8;
}

vector<pair<int, int>> movements = {
    {-1, 2}, {1, 2}, 
    {-1, -2}, {1, -2}, 
    {2, -1}, {2, 1}, 
    {-2, -1}, {-2, 1}
};

int get_x(string s) {
    return s[0] - 'a';
}

int get_y(string s) {
    return s[1] - '1';
}


int bfs(string source, string dest) {
    int sourceX = get_x(source);
    int sourceY = get_y(source);
    int destX = get_x(dest);
    int destY = get_y(dest);

    queue<pair<int, int>> q;
    q.push({sourceX, sourceY});
    vis[sourceX][sourceY] = 1;
    level[sourceX][sourceY] = 0;

    while(!q.empty()) {
        pair<int, int> curr_v = q.front();
        int x = curr_v.first, y = curr_v.second;
        q.pop();

        for (auto movement : movements) {
            int childX = movement.first + x;
            int childY = movement.second + y;
            if (!isValid(childX, childY)) continue;
            if (!vis[childX][childY]) {
                q.push({childX, childY});
                vis[childX][childY] = 1;
                level[childX][childY] = level[x][y] + 1;
            }
        }
        if (level[destX][destY] != inf) {
            break;
        }
    }
    return level[destX][destY];
}

void reset() {
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            vis[i][j] = 0;
            level[i][j] = inf;
        }
    }
}


signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);

    reset();
    string s1, s2;
    cin >> s1 >> s2;
    cout << bfs(s1, s2);

    return 0;
}

