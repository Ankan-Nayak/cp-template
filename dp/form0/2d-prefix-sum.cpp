#include <bits/stdc++.h>
using namespace std;

// Build 2D prefix sum (1-based indexing)
vector<vector<int>> compute2DPrefixSum(const vector<vector<int>>& mat, int n, int m) {
    vector<vector<int>> prefix(n + 1, vector<int>(m + 1, 0));

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            prefix[i][j] = mat[i][j]
                         + prefix[i - 1][j]
                         + prefix[i][j - 1]
                         - prefix[i - 1][j - 1];
        }
    }
    return prefix;
}

// Query prefix sum in submatrix (x1, y1) to (x2, y2)
int query2DPrefixSum(const vector<vector<int>>& prefix, int x1, int y1, int x2, int y2) {
    return prefix[x2][y2]
         - prefix[x1 - 1][y2]
         - prefix[x2][y1 - 1]
         + prefix[x1 - 1][y1 - 1];
}

// Build 2D difference array (1-based indexing)
vector<vector<int>> compute2DDiffArray(const vector<vector<int>>& mat, int n, int m) {
    vector<vector<int>> diff(n + 2, vector<int>(m + 2, 0)); // +2 for safe updates at x2+1, y2+1

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            diff[i][j] = mat[i][j]
                       - mat[i - 1][j]
                       - mat[i][j - 1]
                       + mat[i - 1][j - 1];
        }
    }
    return diff;
}

// Apply value to submatrix (x1, y1) to (x2, y2)
void update2DDiffArray(vector<vector<int>>& diff, int x1, int y1, int x2, int y2, int val) {
    diff[x1][y1]       += val;
    diff[x1][y2 + 1]   -= val;
    diff[x2 + 1][y1]   -= val;
    diff[x2 + 1][y2 + 1] += val;
}

// Reconstruct matrix from 2D difference array
vector<vector<int>> reconstructFromDiffArray(const vector<vector<int>>& diff, int n, int m) {
    vector<vector<int>> mat(n + 1, vector<int>(m + 1, 0));

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            mat[i][j] = diff[i][j]
                      + mat[i - 1][j]
                      + mat[i][j - 1]
                      - mat[i - 1][j - 1];
        }
    }
    return mat;
}
