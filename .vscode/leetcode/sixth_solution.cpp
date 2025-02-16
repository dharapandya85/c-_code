#include <vector>
#include <algorithm>
#include<iostream>
using namespace std;

class Solution {
public:
    int n, m;
    vector<int> sequence = {1, 2, 0, 2, 0};

    int lenOfVDiagonal(vector<vector<int>>& grid) {
        n = grid.size();
        m = grid[0].size();
        
        // Directions: 
        // 0: ↘ (1,1), 1: ↙ (1,-1), 2: ↖ (-1,-1), 3: ↗ (-1,1)
        vector<pair<int, int>> directions = {{1, 1}, {1, -1}, {-1, -1}, {-1, 1}};

        int maxLength = 0;

        // DP array: Stores longest valid segment for each cell per direction
        vector<vector<vector<int>>> dp(n, vector<vector<int>>(m, vector<int>(4, 0)));

        // Iterate through the grid
        for (int x = 0; x < n; ++x) {
            for (int y = 0; y < m; ++y) {
                if (grid[x][y] == 1) {
                    // Start a segment from '1'
                    for (int d = 0; d < 4; ++d) {
                        int length = dfs(grid, x, y, d, 0, false);
                        maxLength = max(maxLength, length);
                    }
                }
            }
        }

        return maxLength;
    }

private:
    int dfs(vector<vector<int>>& grid, int x, int y, int dir, int seqIndex, bool turned) {
        static vector<pair<int, int>> directions = {{1, 1}, {1, -1}, {-1, -1}, {-1, 1}};
        vector<int> sequence = {1, 2, 0, 2, 0};
        int n = grid.size(), m = grid[0].size();

        int length = 1;
        int dx = directions[dir].first;
        int dy = directions[dir].second;
        int nx = x + dx, ny = y + dy;

        // Continue current direction
        if (nx >= 0 && ny >= 0 && nx < n && ny < m && 
            grid[nx][ny] == sequence[(seqIndex + 1) % 5]) {
            length = max(length, 1 + dfs(grid, nx, ny, dir, (seqIndex + 1) % 5, turned));
        }

        // Attempt one clockwise turn if not turned yet
        if (!turned) {
            for (int nextDir = 0; nextDir < 4; ++nextDir) {
                if (nextDir != dir && isClockwise(dir, nextDir)) {
                    int nx = x + directions[nextDir].first;
                    int ny = y + directions[nextDir].second;
                    if (nx >= 0 && ny >= 0 && nx < n && ny < m &&
                        grid[nx][ny] == sequence[(seqIndex + 1) % 5]) {
                        length = max(length, 1 + dfs(grid, nx, ny, nextDir, (seqIndex + 1) % 5, true));
                    }
                }
            }
        }

        return length;
    }

    bool isClockwise(int d1, int d2) {
        vector<int> order = {0, 1, 2, 3}; 
        return (order[(d1 + 1) % 4] == d2);
    }
};
int main(){
    Solution sol;
    vector<vector<int>> grid1 = {{2,2,1,2,2},
        {2,0,2,2,0},
        {2,0,1,1,0},
        {1,0,2,2,2},
        {2,0,0,2,2},
        {1},
    };
    cout << "Test 1: " << sol.lenOfVDiagonal(grid1) << " (Expected: don't know)" << endl;

    vector<vector<int>> grid2 = {{2,1,2,0,1,2,2,2,2,0,2}, {0,1,0,2,1,2,0,0,2,0,}, {2,2,2,2,2,1,1,0,2,2,1},{2,0,1,0,1,0,1,0,0,0,2}};
    cout << "Test 2: " << sol.lenOfVDiagonal(grid2) << " (Expected: test yourself)" << endl;

    return 0;
}