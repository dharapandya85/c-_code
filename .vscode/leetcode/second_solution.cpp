#include<vector>
#include<algorithm>
#include<iostream>
using namespace std;
class Solution{
    public:
    //int n,m;
    //vector<vector<int>> jorvexalin;

    //Directions: diagonals
    vector<pair<int,int>> directions={{1,1},{1,-1},{-1,1},{-1,-1}};
    //vector<int>sequence={1,2,0,2,0}; //V-shaped pattern
    // Recursive DFS to find V-shaped segment
    int dfs(int r, int c, vector<vector<int>> &grid, vector<int> &sequence,int seqIndex, int n, int m, bool turned) {
        int length = 1; 
        int nx = r + directions[seqIndex].first;
        int ny = c + directions[seqIndex].second;

        // Continue in the same diagonal direction
        while (nx >= 0 && ny >= 0 && nx < n && ny < m && grid[nx][ny] == sequence[(length) % sequence.size()]) {
            length++;
            nx += directions[seqIndex].first;
            ny += directions[seqIndex].second;
        }

        // // Try a 90-degree clockwise turn if not used
        // if (!turned) {
        //     for (auto [dx2, dy2] : directions) {
        //         // Only change direction clockwise
        //         if ((dx == 1 && dy == 1 && dx2 == 1 && dy2 == -1) ||
        //             (dx == 1 && dy == -1 && dx2 == -1 && dy2 == -1) ||
        //             (dx == -1 && dy == -1 && dx2 == -1 && dy2 == 1) ||
        //             (dx == -1 && dy == 1 && dx2 == 1 && dy2 == 1)) {
        //             length = max(length, 1 + dfs(nx - dx, ny - dy, seqIndex, dx2, dy2, true));
        //         }
        //     }
        // }

        return length;
    }

    int lenOfVDiagonal(vector<vector<int>>& grid) {
        int n = grid.size();
        int m = grid[0].size();
        //int jorvexalin = grid;
        vector<int> sequence = {1, 2, 0};
        int maxLength = 0;

        // Search from each cell starting with 1
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (grid[i][j] == 1) {
                    for (int d1 = 0; d1 < 4; d1++) {
                        for (int d2 = 0; d2 < 4; d2++) {
                            if (d1 != d2) {
                                maxLength = max(maxLength, dfs(i, j, grid,sequence,n, m, d1, false));
                            }
                        }  
                }
            }
        }
    }

        return maxLength;
    }
};
int main() {
    Solution sol;
    
    // Test Case 1
    vector<vector<int>> grid1 = {
        {0, 1},
        {1, 0}
    };
    cout << "Test 1: " << sol.lenOfVDiagonal(grid1) << " (Expected: 2)" << endl;

    // Test Case 2
    vector<vector<int>> grid2 = {
        {1, 0, 0}, {0, 1, 0}, {0, 0, 1}
    };
    cout << "Test 2: " << sol.lenOfVDiagonal(grid2) << endl;

    

    return 0;
       
}