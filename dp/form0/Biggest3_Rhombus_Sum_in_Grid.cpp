class Solution {
public:
    int diag[200][200], antid[200][200]; 
    int n, m, OFFSET = 60;

    bool isValid(int x, int y) {
        return (x >= 0 && x < n && y >= 0 && y < m);
    }

    vector<int> getBiggestThree(vector<vector<int>>& grid) {
        n = grid.size(), m = grid[0].size();

        for (int i = 0; i < n; ++i) { // '/'
            for (int j = m - 1; j >= 0; --j) {
                antid[i + j][j] = grid[i][j];
                if (j + 1 < m) antid[i + j][j] += antid[i + j][j + 1];
            }
        }

        for (int i = 0; i < n; ++i) { // '\'
            for (int j = 0; j < m; ++j) {
                diag[i - j + OFFSET][j] = grid[i][j];
                if (j - 1 >= 0) diag[i - j + OFFSET][j] += diag[i - j + OFFSET][j - 1];
            }
        }
        

        vector<int> ans;
        // store all ans except single elemnets
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                for (int d = 0; d <= (min(n, m) + 1) / 2; ++d) {
                    int res = 0;
                    if (!isValid(i-d,j) || !isValid(i+d,j) || !isValid(i,j-d) || !isValid(i,j+d)) continue;

                    res += antid[i+j-d][j-d] - antid[i-d+j][j+1]; 
                    res += antid[i+d+j][j] - antid[i+j+d][j+d+1]; 

                    res += diag[i-(j+d)+OFFSET][j+d] - ((j-1 < 0) ? 0 : diag[i-d-j+OFFSET][j-1]);
                    res += diag[i+d-j+OFFSET][j] - ((j-d-1 < 0) ? 0 : diag[i-(j-d)+OFFSET][j-d-1]);

                    // remove duplicates
                    res -= (grid[i-d][j] + grid[i+d][j] + grid[i][j+d] + grid[i][j-d]);
                    ans.push_back(res);
                }
            }
        }

        // for single elements
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                ans.push_back(grid[i][j]);
                cout << ans.back() << endl;
            }
        }

        sort(ans.rbegin(), ans.rend());

        vector<int> answer;
        for (int i = 0; i < (int)ans.size(); ++i) {
            if (answer.size() == 3) break; // top 3
            if (ans[i] == 0) continue; // deafult ans = 0, don't take
            if (answer.size() && answer.back() != ans[i]) answer.push_back(ans[i]); // don't repeat
            else if (answer.size() == 0) answer.push_back(ans[i]);
        }
        return answer;
    }
};




/*
/ -> for this uq id = i+j
\ -> unq id = i - j + OFFSET
from every pos(i,j) go in D distance
*/