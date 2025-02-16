#include <vector>
#include<iostream>
#include <algorithm>
#include<stdio.h>
using namespace std;
class Solution {
    public:
    int lenOfDiagonal(vector<vector<int>>&grid){
        int n= static_cast<int>(grid.size());
        int  m= static_cast<int>(grid[0].size());
        int maxLength = 0;
        vector<vector<int>> jorvexalin=grid;

        //Directions for diagonals:(dx,dy)
        vector<pair<int,int>> directions={{1,1},{1,-1},{-1,1},{-1,-1}};

        //Function to check the longest diagonal segment starting from (r,c)
        auto dfs=[&](int r,int c, int d1, int d2){
            int length=1;
            vector<vector<bool>> visited(n, vector<bool>(m, false));
             visited[r][c] = true;
            int prev = grid[r][c];
            int x= r+directions[d1].first, y= c+directions[d1].second;

            //Follow first diagonal 
            while (x >= 0 && y >= 0 && x < n && y < m && 
                !visited[x][y] && grid[x][y] != prev && grid[x][y] != 0){
                visited[x][y] = true;   
                length++;
                prev=grid[x][y];
                x+=directions[d1].first;
                y+=directions[d1].second;
            }
            //Check second diagonal after a turn
            int tempX=x+directions[d2].first, tempY=y+directions[d2].second;
            while (tempX >= 0 && tempY >= 0 && tempX < n && tempY < m && 
                !visited[tempX][tempY] && grid[tempX][tempY] != prev && grid[tempX][tempY] != 0) {
                visited[tempX][tempY] = true;   
                length++;
                prev=grid[tempX][tempY];
                tempX+=directions[d2].first;
                tempY+=directions[d2].second;
            }
            return length;
        };
        //Iterate through the grid and search for longest V-shaped segment
        for(int i=0;i<static_cast<int>(grid.size());i++){
            for(int j=0;j<static_cast<int>(grid[i].size());j++){
                if(grid[i][j]==1){
                    for(int d1=0;d1<4;d1++){
                        for(int d2=0;d2<4;d2++){
                            if(d1!=d2){
                                maxLength=max(maxLength,dfs(i,j,d1,d2));
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
    cout << "Test 1: " << sol.lenOfDiagonal(grid1) << " (Expected: 2)" << endl;

    // Test Case 2
    vector<vector<int>> grid2 = {
        {0, 1, 0, 2},
        {1, 0, 2, 0},
        {0, 2, 1, 0},
        {2, 0, 0, 1}
    };
    cout << "Test 2: " << sol.lenOfDiagonal(grid2) << endl;

    // ✅ Test Case 3: No diagonal pattern
    vector<vector<int>> grid3 = {
        {0, 0},
        {0, 0}
    };
    cout << "Test 3: " << sol.lenOfDiagonal(grid3) << " (Expected: 0)" << endl;

    return 0;
       
}