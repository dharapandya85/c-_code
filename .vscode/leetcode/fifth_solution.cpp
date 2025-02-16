#include <vector>
#include <unordered_map>
#include<iostream>
using namespace std;

class Solution {
public:
    int n, m;
    vector<vector<int>> grid;
    vector<int> sequence = {1, 2, 0, 2, 0};
    vector<pair<int, int>> directions = {{1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
    
    // Memo: (x, y, seqIndex, direction, turned) -> length
    vector<vector<vector<vector<vector<int>>>>> memo;

    int dfs(int x, int y, int seqIndex, int dirIndex, bool turned) {
        if (memo[x][y][seqIndex][dirIndex][turned] != -1) {
            return memo[x][y][seqIndex][dirIndex][turned];
        }

        int length = 1; // current cell counts
        int dx = directions[dirIndex].first;
        int dy = directions[dirIndex].second;
        int nx = x + dx, ny = y + dy;

        // Continue along the current diagonal if pattern matches
        if (nx >= 0 && ny >= 0 && nx < n && ny < m && 
            grid[nx][ny] == sequence[(seqIndex + 1) % 5]) {
            length = max(length, 1 + dfs(nx, ny, (seqIndex + 1) % 5, dirIndex, turned));
        }

        // Attempt a single clockwise turn if not turned yet
        if (!turned) {
            for (int nextDir = 0; nextDir < 4; nextDir++) {
                if (nextDir != dirIndex && isClockwise(dirIndex, nextDir)) {
                    nx = x + directions[nextDir].first;
                    ny = y + directions[nextDir].second;
                    if (nx >= 0 && ny >= 0 && nx < n && ny < m && 
                        grid[nx][ny] == sequence[(seqIndex + 1) % 5]) {
                        length = max(length, 1 + dfs(nx, ny, (seqIndex + 1) % 5, nextDir, true));
                    }
                }
            }
        }

        return memo[x][y][seqIndex][dirIndex][turned] = length;
    }

    // Check if the direction change is a clockwise 90° turn
    bool isClockwise(int d1, int d2) {
        // Order: Bottom-Right -> Bottom-Left -> Top-Left -> Top-Right
        vector<int> order = {0, 1, 2, 3};
        return (order[(d1 + 1) % 4] == d2);
    }

    int lenOfVDiagonal(vector<vector<int>>& inputGrid) {
        this->grid = inputGrid;
        n = grid.size();
        m = grid[0].size();

        // Initialize memoization: 5D vector
        memo.assign(n, vector<vector<vector<vector<int>>>>(
            m, vector<vector<vector<int>>>(
                5, vector<vector<int>>(
                    4, vector<int>(2, -1)))));

        int maxLength = 0;

        // Search from every cell with value 1
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (grid[i][j] == 1) {
                    for (int d = 0; d < 4; d++) {
                        maxLength = max(maxLength, dfs(i, j, 0, d, false));
                    }
                }
            }
        }

        return maxLength;
    }
};
int main(){
    Solution sol;
    vector<vector<int>> grid1 = {{2,2,1,2,2},
        {2,0,2,2,0},
        {2,0,1,1,0},
        {1,0,2,2,2},
        {2,0,0,2,2}};
    cout << "Test 1: " << sol.lenOfVDiagonal(grid1) << " (Expected: 5/7)" << endl;

    vector<vector<int>> grid2 = {{2,1,2,0,1,2,2,2,2,0,2}, {0,1,0,2,1,2,0,0,2,0,}, {2,2,2,2,2,1,1,0,2,2,1},{2,0,1,0,1,0,1,0,0,0,2}};
    cout << "Test 2: " << sol.lenOfVDiagonal(grid2) << " (Expected: test yourself)" << endl;

    return 0;
}