#include<bits/stdc++.h>
using namespace std;

int n;
string r, c;
vector<string> sol, final_sol;
bool foundSol = false;
string all_done, done;

map<char, int> mp;

// vector<string> all_pos;
vector<string> all_pos[3];
string pos;

bool check (string ch, string done) {
    for (int i = 0; i < n; ++i) {
        if (done[i] == '0'  && ch[i] != '.'  &&  ch[i] != c[i]) return false;
    }
    return true;
}

string newDone(string done, string ch) {
    for (int i = 0; i < n; ++i) {
        if (ch[i] != '.') done[i] = '1';
    }
    return done;
}

bool isValid(vector<string> &sol) {
    for (int j = 0; j < n; ++j) {
        set<char> st;
        for (int i = 0; i < (int)sol.size(); ++i) {
            if (sol[i][j] != '.') st.insert(sol[i][j]);
        }
        if (st.size() != 3) return false;
    }
    return true;
}

void rec(int level, string done) {
    if (foundSol) return;

    if (level == n) {
        if (isValid(sol)  &&  all_done == done) {
            final_sol = sol;
            foundSol = true;
        }
        return;
    }

    for (const string& ch : all_pos[r[level] - 'A']) {
        if (check(ch, done)) {
            sol.push_back(ch);
            rec(level + 1, newDone(done, ch));
            sol.pop_back();
        }
    }
}

void generate(int level) {
    if (level == n) {
        for (int i = 0; i < (int)pos.length(); ++i) {
            if (pos[i] != '.') {
                all_pos[pos[i] - 'A'].push_back(pos);
                break;
            }
        }
        // all_pos.push_back(pos);
        // cout << pos << endl;
        return;
    }

    for (auto &ch : mp) {
        if (ch.second > 0) {
            ch.second--;
            pos.push_back(ch.first);
            generate(level + 1);
            pos.pop_back();
            ch.second++;
        }
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);

    
    cin >> n;
    cin >> r >> c;
    mp['.'] = n - 3;
    mp['A'] = 1;
    mp['B'] = 1;
    mp['C'] = 1;

    for (int i = 0; i < n; ++i) {
        all_done += '1';
        done += '0';
    }

    generate(0);
    rec(0, done);

    if (foundSol) {
        cout << "Yes\n";
        for (const auto& it : final_sol) cout << it << endl;
    } else {
        cout << "No\n";
    }

    return 0;
}