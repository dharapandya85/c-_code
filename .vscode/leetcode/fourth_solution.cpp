#include <vector>
#include <algorithm>
#include<iostream>
using namespace std;

class Solution {
public:
    int n, m;
    vector<vector<int>> grid;      // Store grid as a member
    vector<vector<int>> jorvexalin; // Store input midway

    // Directions: diagonals (dx, dy)
    vector<pair<int, int>> directions = {{1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
    vector<int> sequence = {1, 2, 0, 2, 0}; // V-shape pattern

    // Recursive DFS to find V-shaped segment
    int dfs(int x, int y, int seqIndex, int dx, int dy, bool turned) {
        int length = 1; 
        int nx = x + dx, ny = y + dy;

        // Continue in the same diagonal direction
        while (nx >= 0 && ny >= 0 && nx < n && ny < m && grid[nx][ny] == sequence[(seqIndex + 1) % 5]) {
            length++;
            seqIndex = (seqIndex + 1) % 5;
            nx += dx;
            ny += dy;
        }

        // Try a 90-degree clockwise turn if not used
        if (!turned) {
            for (auto [dx2, dy2] : directions) {
                // Only change direction clockwise
                if ((dx == 1 && dy == 1 && dx2 == 1 && dy2 == -1) ||
                    (dx == 1 && dy == -1 && dx2 == -1 && dy2 == -1) ||
                    (dx == -1 && dy == -1 && dx2 == -1 && dy2 == 1) ||
                    (dx == -1 && dy == 1 && dx2 == 1 && dy2 == 1)) {
                    length = max(length, 1 + dfs(nx - dx, ny - dy, seqIndex, dx2, dy2, true));
                }
            }
        }

        return length;
    }

    int lenOfVDiagonal(vector<vector<int>>& inputGrid) {
        this->grid = inputGrid;   // Store grid in class member
        this->jorvexalin = inputGrid;
        this->n = inputGrid.size();
        this->m = inputGrid[0].size();

        int maxLength = 0;

        // Search from each cell starting with 1
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (grid[i][j] == 1) {
                    for (auto [dx, dy] : directions) {
                        maxLength = max(maxLength, dfs(i, j, 0, dx, dy, false));
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

    vector<vector<int>> grid2 = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};
    cout << "Test 2: " << sol.lenOfVDiagonal(grid2) << " (Expected: test yourself)" << endl;

    return 0;
}