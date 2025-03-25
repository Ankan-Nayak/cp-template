class Solution {
    public:
        void dfs(int i, int j, int initial_color, int new_color, vector<vector<int>> &image) {
          int n = image.size();
          int m = image[0].size();
          if (i < 0  ||  j < 0) return;
          if (i >= n  ||  j >= m) return;
          if (image[i][j] != initial_color) return;
    
          image[i][j] = new_color;
          dfs(i - 1, j, initial_color, new_color, image);
          dfs(i + 1, j, initial_color, new_color, image);
          dfs(i, j - 1, initial_color, new_color, image);
          dfs(i, j + 1, initial_color, new_color, image);
        }
    
        vector<vector<int>> floodFill(vector<vector<int>>& image, int sr, int sc, int new_color) {
          int initial_color = image[sr][sc];
          if (initial_color != new_color) {
            dfs(sr, sc, initial_color, new_color, image);
          }
          return image;
        }
    };