#include <vector>
#include <unordered_map>
#include <string>
#include <queue>
#include <algorithm>
#include<iostream>
using namespace std;

class Solution {
public:
    int n, m;
    vector<int> sequence = {1, 2, 0, 2, 0};
    vector<pair<int, int>> directions = {{1, 1}, {1, -1}, {-1, -1}, {-1, 1}};

    struct State {
        int x, y, dir, seqIndex, turned;
    };

    int lenOfVDiagonal(vector<vector<int>>& grid) {
        n = grid.size();
        m = grid[0].size();
        int maxLength = 0;
        unordered_map<string, int> visited;

        for (int x = 0; x < n; ++x) {
            for (int y = 0; y < m; ++y) {
                if (grid[x][y] == 1) {
                    queue<State> q;
                    for (int d = 0; d < 4; ++d) {
                        q.push({x, y, d, 0, 0});
                        visited[key(x, y, d, 0, 0)] = 1;
                    }

                    while (!q.empty()) {
                        State cur = q.front(); q.pop();
                        int length = visited[key(cur.x, cur.y, cur.dir, cur.seqIndex, cur.turned)];
                        maxLength = max(maxLength, length);

                        // Continue current direction
                        checkNext(grid, visited, q, cur, length, cur.dir);

                        // Try one clockwise turn if not turned
                        if (cur.turned == 0) {
                            int nextDir = (cur.dir + 1) % 4;
                            checkNext(grid, visited, q, cur, length, nextDir, 1);
                        }
                    }
                }
            }
        }
        return maxLength;
    }

private:
    void checkNext(vector<vector<int>>& grid, unordered_map<string, int>& visited,
                   queue<State>& q, State cur, int length, int dir, int turned = -1) {
        int nx = cur.x + directions[dir].first;
        int ny = cur.y + directions[dir].second;
        int nextSeq = (cur.seqIndex + 1) % 5;

        if (valid(nx, ny) && grid[nx][ny] == sequence[nextSeq]) {
            int t = (turned == -1) ? cur.turned : turned;
            string stateKey = key(nx, ny, dir, nextSeq, t);
            if (!visited.count(stateKey)) {
                visited[stateKey] = length + 1;
                q.push({nx, ny, dir, nextSeq, t});
            }
        }
    }

    bool valid(int x, int y) {
        return x >= 0 && y >= 0 && x < n && y < m;
    }

    string key(int x, int y, int dir, int seqIndex, int turned) {
        return to_string(x) + "," + to_string(y) + "," + to_string(dir) + "," + to_string(seqIndex) + "," + to_string(turned);
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
        {2,0,2,2,0},
        {2,2,2,2,2},
        {0,0,2,2,2},
        {2,2,1,2,2},

    };
    cout << "Test 1: " << sol.lenOfVDiagonal(grid1) << " (Expected: don't know)" << endl;

    vector<vector<int>> grid2 = {{2,1,2,0,1,2,2,2,2,0,2}, {0,1,0,2,1,2,0,0,2,0,}, {2,2,2,2,2,1,1,0,2,2,1},{2,0,1,0,1,0,1,0,0,0,2}};
    cout << "Test 2: " << sol.lenOfVDiagonal(grid2) << " (Expected: test yourself)" << endl;

    return 0;
}