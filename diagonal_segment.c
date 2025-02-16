#include<vector>
#include<algorithm>
 
using namespace std;

class Solution{
    public:
    int lenOfDiagonal(vector<vector<int>>&grid){
        int n= grid.size(), m= grid[0].size();
        vector<vector<int>> jorvexalin=grid;

        //Directions for diagonals:(dx,dy)
        vector<pair<int,int>> directions={{1,1},{1,-1},{-1,1},{-1,-1}};

        //Function to check the longest diagonal segment starting from (r,c)
        auto dfs=[&](int r,int c, int d1, int d2){
            int length=1,prev=1;
            int x= r+directions[d1].first, y= c+directions[d1].second;

            //Follow first diagonal 
            while(x>=0 && y>=0 && y<m && grid[x][y]==(prev==1?2:0)){
                length++;
                prev=grid[x][y];
                x+=directions[d1].first;
                y+=directions[d1].second;
            }
            //Check second diagonal after a turn
            int tempX=x+directions[d2].first, tempY=y+directions[d2].second;
            while(tempX>=0 && tempY>=0 && tempX<n && tempY<m && grid[tempX][tempY]==(prev==1?2:0)){
                length++;
                prev=grid[tempX][tempY];
                tempX+=directions[d2].first;
                tempY+=directions[d2].second;
            }
            return length;
        };
        //Iterate through the grid and search for longest V-shaped segment
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
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